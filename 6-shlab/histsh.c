/* 
 * tsh - A tiny shell program with job control
 * 
 * <Put your name and login ID here>
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

/* Misc manifest constants */
#define MAXLINE    1024   /* max line size */
#define MAXARGS     128   /* max args on a command line */
#define MAXJOBS      16   /* max jobs at any point in time */
#define MAXJID    1<<16   /* max job ID */

/* Job states */
#define UNDEF 0 /* undefined */
#define FG 1    /* running in foreground */
#define BG 2    /* running in background */
#define ST 3    /* stopped */

/* 
 * Jobs states: FG (foreground), BG (background), ST (stopped)
 * Job state transitions and enabling actions:
 *     FG -> ST  : ctrl-z
 *     ST -> FG  : fg command
 *     ST -> BG  : bg command
 *     BG -> FG  : fg command
 * At most 1 job can be in the FG state.
 */

/* Global variables */
extern char **environ;      /* defined in libc */
char prompt[] = "tsh> ";    /* command line prompt (DO NOT CHANGE) */
int verbose = 0;            /* if true, print additional output */
int nextjid = 1;            /* next job ID to allocate */
char sbuf[MAXLINE];         /* for composing sprintf messages */

struct job_t {              /* The job struct */
    pid_t pid;              /* job PID */
    int jid;                /* job ID [1, 2, ...] */
    int state;              /* UNDEF, BG, FG, or ST */
    char cmdline[MAXLINE];  /* command line */
};
struct job_t jobs[MAXJOBS]; /* The job list */
/* End global variables */
volatile sig_atomic_t p_id;

/* Function prototypes */

/* Here are the functions that you will implement */
void eval(char *cmdline);
int builtin_cmd(char **argv);
void do_bgfg(char **argv);
void waitfg(pid_t pid);

void sigchld_handler(int sig);
void sigtstp_handler(int sig);
void sigint_handler(int sig);

/* Here are helper routines that we've provided for you */
int parseline(const char *cmdline, char **argv); 
void sigquit_handler(int sig);

void clearjob(struct job_t *job);
void initjobs(struct job_t *jobs);
int maxjid(struct job_t *jobs); 
int addjob(struct job_t *jobs, pid_t pid, int state, char *cmdline);
int deletejob(struct job_t *jobs, pid_t pid); 
pid_t fgpid(struct job_t *jobs);
struct job_t *getjobpid(struct job_t *jobs, pid_t pid);
struct job_t *getjobjid(struct job_t *jobs, int jid); 
int pid2jid(pid_t pid); 
void listjobs(struct job_t *jobs);

void usage(void);
void unix_error(char *msg);
void app_error(char *msg);
void wait_handler(int sig);
typedef void handler_t(int);
handler_t *Signal(int signum, handler_t *handler);
/*
 * main - The shell's main routine 
 */
int main(int argc, char **argv) 
{
    char c;
    char cmdline[MAXLINE];
    int emit_prompt = 1; /* emit prompt (default) */



    /* Redirect stderr to stdout (so that driver will get all output
     * on the pipe connected to stdout) */
    dup2(1, 2);

    /* Parse the command line */
    while ((c = getopt(argc, argv, "hvp")) != EOF) {
        switch (c) {
        case 'h':             /* print help message */
            usage();
	    break;
        case 'v':             /* emit additional diagnostic info */
            verbose = 1;
	    break;
        case 'p':             /* don't print a prompt */
            emit_prompt = 0;  /* handy for automatic testing */
	    break;
	default:
            usage();
	}
    }

    

    /* Install the signal handlers */

    /* These are the ones you will need to implement */
    Signal(SIGINT,  sigint_handler);   /* ctrl-c */
    Signal(SIGTSTP, sigtstp_handler);  /* ctrl-z */
    Signal(SIGCHLD, sigchld_handler);  /* Terminated or stopped child */

    /* This one provides a clean way to kill the shell */
    Signal(SIGQUIT, sigquit_handler); 

    /* Initialize the job list */
    initjobs(jobs);

    /* Execute the shell's read/eval loop */
    while (1) {

	/* Read command line */
	if (emit_prompt) {
	    printf("%s", prompt);
	    fflush(stdout);
	}
	if ((fgets(cmdline, MAXLINE, stdin) == NULL) && ferror(stdin))
	    app_error("fgets error");
	if (feof(stdin)) { /* End of file (ctrl-d) */
	    fflush(stdout);
	    exit(0);
	}

	/* Evaluate the command line */
	eval(cmdline);
	fflush(stdout);
	fflush(stdout);
    } 

    exit(0); /* control never reaches here */

    //此时要把那些运行结束的后台进程给回收了 

    
}
  
/* 
 * eval - Evaluate the command line that the user has just typed in
 * 
 * If the user has requested a built-in command (quit, jobs, bg or fg)
 * then execute it immediately. Otherwise, fork a child process and
 * run the job in the context of the child. If the job is running in
 * the foreground, wait for it to terminate and then return.  Note:
 * each child process must have a unique process group ID so that our
 * background children don't receive SIGINT (SIGTSTP) from the kernel
 * when we type ctrl-c (ctrl-z) at the keyboard.  
*/
void eval(char *cmdline) 
{
    char *argv[MAXARGS]; //argument list execve()
    char buf[MAXLINE];  //modified command line
    int bg; //decides whether the job runs in bg or fg
    pid_t pid; //process id
    int status;


    
    strcpy(buf,cmdline);
    bg  = parseline(buf,argv);
    if(bg)
        status=2;
    else
        status=1;

    if(argv[0]==NULL){ //empty line case
        return;
    }

    /* Install the block signal sets */
    sigset_t  mask_all,mask_one,prev_one;

    sigfillset(&mask_all);
    sigemptyset(&mask_one);
    sigaddset(&mask_one,SIGCHLD);


    if(!builtin_cmd(argv)){ //non-builtin command case
        //阻塞sigchild,为了防止在add_job之前delete_job
        sigprocmask(SIG_BLOCK,&mask_one,&prev_one);
        if((pid = fork())==0){ //Child runs user job
            setpgid(0,0);   //修改进程组
            sigprocmask(SIG_SETMASK,&prev_one,NULL); 
            
            if(execve(argv[0],argv,environ)<0){
                printf("Command Invalid\n"); //when input an invalid command
                exit(0); 
            }
            exit(0);
        }else
        {
            //阻塞一切，为了加入此job
            sigprocmask(SIG_BLOCK,&mask_all,NULL);
            addjob(jobs,pid,status,cmdline);
            sigprocmask(SIG_SETMASK,&mask_one,NULL);    //阻塞sigchild
            //Parent waits for foreground job to terminate
            if(!bg){        //child process
                //是前台进程才会修改那个原子p_id
                waitfg(pid);        //前台进程要等回收结束才会让下一个命令输入
            }else{
                printf("[%d] %s",pid,cmdline);
                //后台进程不需要等，只打印命令，然后前台继续执行
            }
            sigprocmask(SIG_SETMASK,&prev_one,NULL);
        }
        
         
    }
    
    return;
}

/* 
 * parseline - Parse the command line and build the argv array.
 * 
 * Characters enclosed in single quotes are treated as a single
 * argument.  Return true if the user has requested a BG job, false if
 * the user has requested a FG job.  
 */
int parseline(const char *cmdline, char **argv) 
{
    static char array[MAXLINE]; /* holds local copy of command line */
    char *buf = array;          /* ptr that traverses command line */
    char *delim;                /* points to first space delimiter */
    int argc;                   /* number of args */
    int bg;                     /* background job? */

    strcpy(buf, cmdline);
    buf[strlen(buf)-1] = ' ';  /* replace trailing '\n' with space */
    while (*buf && (*buf == ' ')) /* ignore leading spaces */
	buf++;

    /* Build the argv list */
    argc = 0;
    if (*buf == '\'') {
	buf++;
	delim = strchr(buf, '\'');
    }
    else {
	delim = strchr(buf, ' ');
    }

    while (delim) {
	argv[argc++] = buf;
	*delim = '\0';
	buf = delim + 1;
	while (*buf && (*buf == ' ')) /* ignore spaces */
	       buf++;

	if (*buf == '\'') {
	    buf++;
	    delim = strchr(buf, '\'');
	}
	else {
	    delim = strchr(buf, ' ');
	}
    }
    argv[argc] = NULL;
    
    if (argc == 0)  /* ignore blank line */
	return 1;

    /* should the job run in the background? */
    if ((bg = (*argv[argc-1] == '&')) != 0) {
	argv[--argc] = NULL;
    }
    return bg;
}

/* 
 * builtin_cmd - If the user has typed a built-in command then execute
 *    it immediately.  
 */
//recognize it is a back('&') or fore(right now executable) or quit 
int builtin_cmd(char **argv) 
{
    sigset_t  mask_all,prev_;

    sigfillset(&mask_all);

    if(!strcmp(argv[0],"quit")){ //when user input quit
        exit(0);
    }
    if(!strcmp(argv[0],"bg")||!strcmp(argv[0],"fg")){//when user imput bg or fg
        do_bgfg(argv);
        return 1;
    }
    else if(!strcmp(argv[0], "jobs")){
        sigprocmask(SIG_SETMASK,&mask_all,&prev_);
        listjobs(jobs);
        sigprocmask(SIG_SETMASK,&prev_,NULL);
        return 1;
    }

    return 0;     /* child process */
}

/* 
 * do_bgfg - Execute the builtin bg and fg commands
 */
void do_bgfg(char **argv) 
{
    char *Jid;
    int id=0;
    struct job_t *jb;
    pid_t jpid;


    sigset_t  mask_all,prev_,mask_one;
    sigfillset(&mask_all);
    sigaddset(&mask_one,SIGCHLD);

    if(!argv[1]){
        printf("please input Jid or Pid\n");
        return;
    }
    Jid=argv[1];

    sigprocmask(SIG_BLOCK,&mask_all,&prev_);
    if(*Jid=='%'){
        
        id=atoi(++Jid);
        printf("%d",id);
        jb=getjobjid(jobs,id);  //输入的id是jobid
        if(!jb)
        {
            printf("No this process!\n");
            sigprocmask(SIG_SETMASK,&prev_,NULL);
            return;
        }
        jpid=jb->pid;
        //除了是ST之外，是BG，则啥也不干
    }
    else {
        
        jpid=atoi(Jid);
        jb=getjobpid(jobs,jpid);
        if(!jb)
        {
            printf("No this process!\n");
            sigprocmask(SIG_SETMASK,&prev_,NULL);
            return;
        }
    }
    

    
    if(!strcmp(argv[0],"bg")){// Change a stopped background job to a running background job.
        switch (jb->state)
        {
        case BG:
            /* 啥也不干 */
            break;
        case ST:
        //接下来是给停止的这个信号发送继续的信号,阻塞信号集，防止此时退出终端
            
            jb->state=BG;
            kill(-jpid,SIGCONT);
            printf("[%d] (%d) %s", jb->jid, jb->pid, jb->cmdline);
            
            break;
        case UNDEF:
        case FG:
            unix_error("bg 出现undef或者FG的进程\n");
            break;
        default:
            break;
        }
    
    
    }
    else if(!strcmp(argv[0],"fg")){  //Change a stopped or running background job to a running in the foreground
        switch (jb->state)
        {
        case FG:
        case UNDEF:
            unix_error("fg 出现undef或者FG的进程\n");
            break;
        default :
            sigprocmask(SIG_BLOCK,&mask_all,&prev_);
            if(jb->state==ST)       //if stopped ,change to run
                kill(-jpid,SIGCONT);
            jb->state=FG;
            sigprocmask(SIG_SETMASK,&mask_one,NULL);
            waitfg(jpid);       //此时是前台进程就必须等待此进程被回收结束
            break;
    }
    
    }
    sigprocmask(SIG_SETMASK,&prev_,NULL);
    return;
}

/* 
 * waitfg - Block until process pid is no longer the foreground process
 */
void waitfg(pid_t pid)
{
    sigset_t mask;
    sigemptyset(&mask);
    p_id=0;
    
    //若未错误，应该是没有阻塞sigchild的信号集
    while (p_id==0){
        sigsuspend(&mask);      //此时挂起该进程，然后等收到sigchild信号时，再恢复原先的信号集
    }
        
    //这一步是为了等回收刚刚处理完毕的前台进程，然后释放出前台shell，让用户输入下一个命令
    return;
}

/*****************
 * Signal handlers
 *****************/

/* 
 * sigchld_handler - The kernel sends a SIGCHLD to the shell whenever
 *     a child job terminates (becomes a zombie), or stops because it
 *     received a SIGSTOP or SIGTSTP signal. The handler reaps all
 *     available zombie children, but doesn't wait for any other
 *     currently running children to terminate.  
 */
void sigchld_handler(int sig) 
{
    int old_errno=errno;
    sigset_t mask_all,prev_all;
    struct job_t *jb;
    pid_t pid;
    int status;
    sigfillset(&mask_all);
    //设置不阻塞
    
    while((pid=waitpid(-1,&status,WNOHANG|WUNTRACED))>0)
    {
        sigprocmask(SIG_BLOCK,&mask_all,&prev_all);
          if(pid == fgpid(jobs)){
            p_id = 1;
            }
             
        jb=getjobpid(jobs,pid);
        
        if(WIFSTOPPED(status)){
            
            //子进程停止引起的waitpid函数返回
            jb->state = ST;
            printf("Job [%d] (%d) stop by signal %d\n", jb->jid, jb->pid, WSTOPSIG(status));
        }else {
            if(WIFSIGNALED(status)){
            //子进程终止引起的返回,这里主要是sigint的信号过来的
            printf("Job [%d] (%d) terminated by signal %d\n", jb->jid, jb->pid, WTERMSIG(status));
           
            
        }
         //只有除了sigstop之外的信号，有sigint和正常的sigchild都需要删除job
        deletejob(jobs,pid);
        }
        
        //不能在这里删除job，因为sigstop的信号也会进来，虽然我也不知道为啥
        //deletejob(jobs,pid);     //此时这个这个子进程被回收了
                    //可以让shell终端开始下一次命令的输入了
        sigprocmask(SIG_SETMASK,&prev_all,NULL);
    }
    
    errno=old_errno;
}

/* 
 * sigint_handler - The kernel sends a SIGINT to the shell whenver the
 *    user types ctrl-c at the keyboard.  Catch it and send it along
 *    to the foreground job.  
 */
void sigint_handler(int sig) 
{
    //杀死前台进程，此时必须向前台进程发送死亡信号，并且需要删除job
    
    int olderrno = errno;
    sigset_t mask_all,prev_all;
    pid_t pid;
    struct job_t *jb;
    sigfillset(&mask_all);
    
    sigprocmask(SIG_BLOCK,&mask_all,&prev_all);
    pid=fgpid(jobs);
    sigprocmask(SIG_SETMASK,&prev_all,NULL);


    if(pid){
        //jb=pid2jid(pid);
        //deletejob(jobs,pid);     //此时这个这个子进程被回收了
        //当给这个进程发sigint信号时，那么就相当于杀死这个进程
        //然后父进程就会收到signal child 然后回收子进程
        //在child handle 函数中，有delete job的工作
        kill(-pid,SIGINT);      
        
    }
    else{
        printf("终止该进程前已经死了\n");
    }
    
    errno = olderrno;
    return;
}

/*
 * sigtstp_handler - The kernel sends a SIGTSTP to the shell whenever
 *     the user types ctrl-z at the keyboard. Catch it and suspend the
 *     foreground job by sending it a SIGTSTP.  
 */
void sigtstp_handler(int sig) 
{
    int olderrno = errno;
    sigset_t mask_all,prev_all;
    pid_t pid;
    struct job_t *curr_job;
    sigfillset(&mask_all);
    sigprocmask(SIG_BLOCK,&mask_all,&prev_all);
    pid=fgpid(jobs);
    if(pid){
        //curr_job=getjobpid(jobs,pid);
        //curr_job->state=ST;   
        kill(-pid,SIGTSTP);
        //这一步很关键，此时waitfg还在等待前台进程回收，但是此时已经有个stop信号过来了
        //此时前台进程被终止，但是shell会接受新的命令
        //因此要让waitfg结束  
        //printf("Job [%d] (%d) stopped by signal 20\n", curr_job->jid, curr_job->pid);
    }  
    sigprocmask(SIG_SETMASK,&prev_all,NULL);
    errno = olderrno;
    return;
}

/*********************
 * End signal handlers
 *********************/

/***********************************************
 * Helper routines that manipulate the job list
 **********************************************/

/* clearjob - Clear the entries in a job struct */
void clearjob(struct job_t *job) {
    job->pid = 0;
    job->jid = 0;
    job->state = UNDEF;
    job->cmdline[0] = '\0';
}

/* initjobs - Initialize the job list */
void initjobs(struct job_t *jobs) {
    int i;

    for (i = 0; i < MAXJOBS; i++)
	clearjob(&jobs[i]);
}

/* maxjid - Returns largest allocated job ID */
int maxjid(struct job_t *jobs) 
{
    int i, max=0;

    for (i = 0; i < MAXJOBS; i++)
	if (jobs[i].jid > max)
	    max = jobs[i].jid;
    return max;
}

/* addjob - Add a job to the job list */
int addjob(struct job_t *jobs, pid_t pid, int state, char *cmdline) 
{
    int i;
    
    if (pid < 1)
	return 0;
    for (i = 0; i < MAXJOBS; i++) {
	if (jobs[i].pid == 0) {
	    jobs[i].pid = pid;
	    jobs[i].state = state;
	    jobs[i].jid = nextjid++;
	    if (nextjid > MAXJOBS)
		nextjid = 1;
	    strcpy(jobs[i].cmdline, cmdline);
  	    if(verbose){
	        printf("Added job [%d] %d %s\n", jobs[i].jid, jobs[i].pid, jobs[i].cmdline);
            }
            return 1;
	}
    }
    printf("Tried to create too many jobs\n");
    return 0;
}

/* deletejob - Delete a job whose PID=pid from the job list */
int deletejob(struct job_t *jobs, pid_t pid) 
{
    int i;

    if (pid < 1)
	return 0;

    for (i = 0; i < MAXJOBS; i++) {
	if (jobs[i].pid == pid) {
	    clearjob(&jobs[i]);
	    nextjid = maxjid(jobs)+1;
	    return 1;
	}
    }
    return 0;
}

/* fgpid - Return PID of current foreground job, 0 if no such job */
pid_t fgpid(struct job_t *jobs) {
    int i;
    int status=1;
    for (i = 0; i < MAXJOBS; i++)
    {
        if (jobs[i].state == status)
    {
        return jobs[i].pid;
    }
    }

    return 0;
}

/* getjobpid  - Find a job (by PID) on the job list */
struct job_t *getjobpid(struct job_t *jobs, pid_t pid) {
    int i;

    if (pid < 1)
	return NULL;
    for (i = 0; i < MAXJOBS; i++)
	if (jobs[i].pid == pid)
	    return &jobs[i];
    return NULL;
}

/* getjobjid  - Find a job (by JID) on the job list */
struct job_t *getjobjid(struct job_t *jobs, int jid) 
{
    int i;

    if (jid < 1)
	return NULL;
    for (i = 0; i < MAXJOBS; i++)
	if (jobs[i].jid == jid)
	    return &jobs[i];
    return NULL;
}

/* pid2jid - Map process ID to job ID */
int pid2jid(pid_t pid) 
{
    int i;
    if (pid < 1)
	    return 0;
    for (i = 0; i < MAXJOBS; i++){
        if (jobs[i].pid == pid) {
            return jobs[i].jid;
        }
    }
    return 0;
}

/* listjobs - Print the job list */
void listjobs(struct job_t *jobs) 
{
    int i;
    
    for (i = 0; i < MAXJOBS; i++) {
	if (jobs[i].pid != 0) {
	    printf("[%d] (%d) ", jobs[i].jid, jobs[i].pid);
	    switch (jobs[i].state) {
		case BG: 
		    printf("Running ");
		    break;
		case FG: 
		    printf("Foreground ");
		    break;
		case ST: 
		    printf("Stopped ");
		    break;
	    default:
		    printf("listjobs: Internal error: job[%d].state=%d ", 
			   i, jobs[i].state);
	    }
	    printf("%s", jobs[i].cmdline);
	}
    }
}
/******************************
 * end job list helper routines
 ******************************/


/***********************
 * Other helper routines
 ***********************/

/*
 * usage - print a help message
 */
void usage(void) 
{
    printf("Usage: shell [-hvp]\n");
    printf("   -h   print this message\n");
    printf("   -v   print additional diagnostic information\n");
    printf("   -p   do not emit a command prompt\n");
    exit(1);
}

/*
 * unix_error - unix-style error routine
 */
void unix_error(char *msg)
{
    fprintf(stdout, "%s: %s\n", msg, strerror(errno));
    exit(1);
}

/*
 * app_error - application-style error routine
 */
void app_error(char *msg)
{
    fprintf(stdout, "%s\n", msg);
    exit(1);
}

/*
 * Signal - wrapper for the sigaction function
 */
handler_t *Signal(int signum, handler_t *handler) 
{
    struct sigaction action, old_action;

    action.sa_handler = handler;  
    sigemptyset(&action.sa_mask); /* block sigs of type being handled */
    action.sa_flags = SA_RESTART; /* restart syscalls if possible */

    if (sigaction(signum, &action, &old_action) < 0)
	unix_error("Signal error");
    return (old_action.sa_handler);
} 



/*
 * sigquit_handler - The driver program can gracefully terminate the
 *    child shell by sending it a SIGQUIT signal.
 */
void sigquit_handler(int sig) 
{
    printf("Terminating after receipt of SIGQUIT signal\n");
    exit(1);
}



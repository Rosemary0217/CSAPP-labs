/* 
 * tsh - A tiny shell program with job control
 * 
 * name: 刘婧婷
 * id： 1120201050
 */

#define _POSIX_C_SOURCE 200809L

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
    char *argv[MAXARGS];//存放拆分的cmdline参数
    char buf[MAXARGS];//存放cmdline的拷贝
    pid_t pid;
    sigset_t mask_all,mask_child,prev_child;
    sigfillset(&mask_all);
    sigemptyset(&mask_child);
    sigaddset(&mask_child, SIGCHLD);
    int bg;
    memset(argv, 0, sizeof(argv));
    strcpy(buf, cmdline);
    bg = parseline(buf, argv);
    if (argv[0]==NULL)
    {
        //printf("err：输入参数无效\n");
        return;
    }
 
    if (!builtin_cmd(argv))
    {
        sigprocmask(SIG_BLOCK, &mask_child, &prev_child);//在开启进程时不接受子进程结束的信号
        if ((pid=fork())==0)
        {
            sigprocmask(SIG_UNBLOCK, &prev_child, NULL);//在子进程中重开起接受子进程的信号
            setpgid(0,0);//修改子进程的组ID变成自己的进程ID，这样当接收SIGINT信号时就不会被一起杀死了
            if (execve(argv[0],argv,environ)<0)
            {
                printf("%s:command not found\n",argv[0]);
                exit(0);
            }
 
        }
 
        sigprocmask(SIG_BLOCK, &mask_all, NULL);//在修改jobs时，阻塞所有信号，结束后再开启
        addjob(jobs, pid, bg+1, cmdline);//状态和bg刚好差1 
        sigprocmask(SIG_SETMASK, &prev_child, NULL); 
 
        if (!bg)//判断是在前台还是在后台运行
        {
            //前台运行
            waitfg(pid);
        }
        else
        {
            //后台运行
            printf("[%d] (%d) %s", pid2jid(pid), pid, cmdline);
        }
          
    }
    return;
}


void eval_ori(char *cmdline) 
{
    char* argv[MAXARGS];
    //memset(argv, '\0', sizeof(argv));
    int is_bg = parseline(cmdline, argv);

    if(argv[0] == NULL)
        return;

    pid_t pid;
    sigset_t mask, mask_child, prev_child;
    sigfillset(&mask);
    sigemptyset(&mask_child);
    sigaddset(&mask_child, SIGCHLD);

    if (builtin_cmd(argv))
        return;

    else{
        sigprocmask(SIG_BLOCK, &mask_child, &prev_child);   //fork之前阻塞子进程信号
        if ((pid=fork())==0)
        {
            setpgid(0,0);      //修改子进程的组ID变成自己的进程ID，这样当接收SIGINT信号时就不会被一起杀死了
            sigprocmask(SIG_UNBLOCK, &prev_child, NULL);   //在子进程中重接受子进程的信号
            if (execve(argv[0],argv,environ)<0)
            {
                printf("%s Command not found\n",argv[0]);
                exit(0);
            }
            exit(0);
        }
        else
        {
            sigprocmask(SIG_BLOCK, &mask, NULL);       //在修改jobs时，阻塞所有信号，结束后再开启
            if(is_bg)
            {
                addjob(jobs, pid, BG, cmdline);         
                // sigprocmask(SIG_SETMASK, &prev_child, NULL); 
                sigprocmask(SIG_SETMASK,&mask_child,NULL);    //阻塞sigchild
                printf("[%d] (%d) %s", pid2jid(pid), pid, cmdline);
            }
            else
            {
                addjob(jobs, pid, FG, cmdline);       
                //sigprocmask(SIG_SETMASK, &prev_child, NULL); 
                sigprocmask(SIG_SETMASK,&mask_child,NULL);    //阻塞sigchild
                waitfg(pid);
            }
            sigprocmask(SIG_SETMASK,&prev_child,NULL);    //阻塞sigchild
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
int builtin_cmd(char **argv) 
{
    if (strcmp(argv[0],"quit")==0)
        exit(0);
    else if (strcmp(argv[0],"bg")==0||strcmp(argv[0],"fg")==0)
    {
        do_bgfg(argv);
        return 1;
    }
    else if (strcmp(argv[0],"jobs")==0){
        listjobs(jobs);
        return 1;
    }
    return 0;     /* not a builtin command */
}

/* 
 * do_bgfg - Execute the builtin bg and fg commands
 */
void do_bgfg(char **argv) 
{
    int pid,jid;
    if (argv[1]==NULL)
    {
        printf("the command requires PID or %%job argument\n");
        return;
    }
    char* tempcmd=argv[1];
    char* ch;
    if ((ch=strchr(tempcmd,'%'))==NULL)
    {
        if ((pid = atoi(tempcmd))==0 && strcmp(tempcmd, "0"))
        {
            printf("the argument of command must be number\n");
            return;
        }
        jid=pid2jid(pid);
        
    }
    else
    {
        tempcmd=ch+1;
        if ((jid = atoi(tempcmd))==0 && strcmp(tempcmd, "0"))
        {
            printf("the argument of command must be number\n");
            return;
        }
    }
    
    if (!strcmp(argv[0],"bg"))
    {
        if (getjobjid(jobs, jid)==NULL)
        {
            printf("No such job\n");
            return;
        }
        getjobjid(jobs, jid)->state = BG;
        pid = getjobjid(jobs, jid)->pid;
        kill(-pid, SIGCONT); 
        printf("Job [%d] (%d) %s", jid, pid, getjobjid(jobs, jid)->cmdline);
    }
    else
    {
        if (getjobjid(jobs, jid)==NULL)
        {
            printf("No such job\n");
            return;
        }
        getjobjid(jobs, jid)->state = FG;
        pid = getjobjid(jobs, jid)->pid;
        kill(-pid, SIGCONT); 
        waitfg(pid);
    }
    
    return;
}
// void do_bgfg(char **argv) 
// {
//     char *name = argv[0];
//     char *id = argv[1];
//     if(id == NULL)
//     {   
//         printf("%s command requires PID or %%jobid argument\n", name);
//         return;
//     }
//     struct job_t* pjob;
//     int pid;
//     if(id[0]=='%')   // id为jid
//     {      
//         int jid = atoi(id+1);
//         if(jid==0){
//             printf("%s argument must be PID or %%jobid\n", name);
//             return;
//         }
//         pjob = getjobjid(jobs, jid);
//         if(pjob==NULL){
//             printf("%d: No such job\n", jid);
//             return;
//         }
//         pid = pjob->pid;
//     }
//     else
//     {
//         pid = atoi(id);
//         if(pid==0){
//             printf("%s argument must be PID or %%jobid\n", name);
//             return;
//         }
//         pjob = getjobpid(jobs, pid);
//         if(pjob==NULL){
//             printf("%d: No such process\n", pid);
//             return;
//         }
//     }
//     kill(-pid, SIGCONT);
//     if(strcmp(name, "bg")==0){
//         pjob->state = BG;
//         printf("[%d] (%d) %s",pid2jid(pid), pid, pjob->cmdline);
//     }
//     else if(strcmp(name, "fg")==0){
//         pjob->state = FG;
//         waitfg(pid);
//     }

//     return;
// }

// void do_bgfg(char **argv) 
// {
//     char *Jid;
//     int id=0;
//     struct job_t *jb;
//     pid_t jpid;


//     sigset_t  mask_all,prev_,mask_one;
//     sigfillset(&mask_all);
//     sigaddset(&mask_one,SIGCHLD);

//     if(!argv[1]){
//         printf("please input Jid or Pid\n");
//         return;
//     }
//     Jid=argv[1];

//     sigprocmask(SIG_BLOCK,&mask_all,&prev_);
//     if(*Jid=='%'){
        
//         id=atoi(++Jid);
//         printf("%d",id);
//         jb=getjobjid(jobs,id);  //输入的id是jobid
//         if(!jb)
//         {
//             printf("No this process!\n");
//             sigprocmask(SIG_SETMASK,&prev_,NULL);
//             return;
//         }
//         jpid=jb->pid;
//         //除了是ST之外，是BG，则啥也不干
//     }
//     else {
        
//         jpid=atoi(Jid);
//         jb=getjobpid(jobs,jpid);
//         if(!jb)
//         {
//             printf("No this process!\n");
//             sigprocmask(SIG_SETMASK,&prev_,NULL);
//             return;
//         }
//     }
    

    
//     if(!strcmp(argv[0],"bg")){// Change a stopped background job to a running background job.
//         switch (jb->state)
//         {
//         case BG:
//             /* 啥也不干 */
//             break;
//         case ST:
//         //接下来是给停止的这个信号发送继续的信号,阻塞信号集，防止此时退出终端
            
//             jb->state=BG;
//             kill(-jpid,SIGCONT);
//             printf("[%d] (%d) %s", jb->jid, jb->pid, jb->cmdline);
            
//             break;
//         case UNDEF:
//         case FG:
//             unix_error("bg 出现undef或者FG的进程\n");
//             break;
//         default:
//             break;
//         }
    
    
//     }
//     else if(!strcmp(argv[0],"fg")){  //Change a stopped or running background job to a running in the foreground
//         switch (jb->state)
//         {
//         case FG:
//         case UNDEF:
//             unix_error("fg 出现undef或者FG的进程\n");
//             break;
//         default :
//             sigprocmask(SIG_BLOCK,&mask_all,&prev_);
//             if(jb->state==ST)       //if stopped ,change to run
//                 kill(-jpid,SIGCONT);
//             jb->state=FG;
//             sigprocmask(SIG_SETMASK,&mask_one,NULL);
//             waitfg(jpid);       //此时是前台进程就必须等待此进程被回收结束
//             break;
//     }
    
//     }
//     sigprocmask(SIG_SETMASK,&prev_,NULL);
//     return;
// }

/* 
 * waitfg - Block until process pid is no longer the foreground process
 */
// void waitfg(pid_t pid)
// {
//     sigset_t mask, prev_mask;
//     sigfillset(&mask);
//     pid_t fg_pid;
//     //等待直到没有前台作业(只等待不回收)
//     while(1){
//         sigsuspend(&mask); //保证原子性，等待信号中断并返回
//         //访问jobs之前阻塞所有信号
//         sigprocmask(SIG_BLOCK, &mask, &prev_mask);
//         if((fg_pid=fgpid(jobs))==0){
// 	    sigprocmask(SIG_SETMASK, &prev_mask, NULL);
//             break;
// 	}
// 	else
// 	    sigprocmask(SIG_SETMASK, &prev_mask, NULL);
//     }


//     return;
// }

void waitfg(pid_t pid)
{
    while (fgpid(jobs))
    {
        usleep(100);
    }
    
    return;
}

/*****************
 * Signal handlers
 *****************/

// /* 
//  * sigchld_handler - The kernel sends a SIGCHLD to the shell whenever
//  *     a child job terminates (becomes a zombie), or stops because it
//  *     received a SIGSTOP or SIGTSTP signal. The handler reaps all
//  *     available zombie children, but doesn't wait for any other
//  *     currently running children to terminate.  
//  */
// void sigchld_handler(int sig) 
// {
//     int old_errno=errno;
//     sigset_t mask_all,prev_all;
//     struct job_t *jb;
//     pid_t pid;
//     int status;
//     sigfillset(&mask_all);
//     //设置不阻塞
    
//     while((pid=waitpid(-1,&status,WNOHANG|WUNTRACED))>0)
//     {
//         sigprocmask(SIG_BLOCK,&mask_all,&prev_all);
//           if(pid == fgpid(jobs)){
//             p_id = 1;
//             }
             
//         jb=getjobpid(jobs,pid);
        
//         if(WIFSTOPPED(status)){
            
//             //子进程停止引起的waitpid函数返回
//             jb->state = ST;
//             printf("Job [%d] (%d) stop by signal %d\n", jb->jid, jb->pid, WSTOPSIG(status));
//         }else {
//             if(WIFSIGNALED(status)){
//             //子进程终止引起的返回,这里主要是sigint的信号过来的
//             printf("Job [%d] (%d) terminated by signal %d\n", jb->jid, jb->pid, WTERMSIG(status));
           
            
//         }
//          //只有除了sigstop之外的信号，有sigint和正常的sigchild都需要删除job
//         deletejob(jobs,pid);
//         }
        
//         //不能在这里删除job，因为sigstop的信号也会进来，虽然我也不知道为啥
//         //deletejob(jobs,pid);     //此时这个这个子进程被回收了
//                     //可以让shell终端开始下一次命令的输入了
//         sigprocmask(SIG_SETMASK,&prev_all,NULL);
//     }
    
//     errno=old_errno;
// }
// // void sigchld_handler(int sig) 
// // {
// //     sigset_t mask, prev_mask;
// //     struct job_t *pjob = malloc(sizeof(struct job_t));
// //     sigfillset(&mask);
// //     int oldErrno = errno;
// //     pid_t pid;
// //     int status;
// //     //访问jobs之前阻塞所有信号
// //     sigprocmask(SIG_BLOCK, &mask, &prev_mask);
// //     while((pid = waitpid(-1, &status, WNOHANG|WUNTRACED))!= 0){
// //         //正常退出
// //         if(WIFEXITED(status))
// //             deletejob(jobs, pid);
// //         //终止
// //         else if(WIFSIGNALED(status)){
// //             printf("Job [%d] (%d) terminated by signal %d\n", pid2jid(pid), pid, WTERMSIG(status));
// //             deletejob(jobs, pid);
// //         }
// //         //停止
// //         else if(WIFSTOPPED(status)){
// //             printf("Job [%d] (%d) stopped by signal %d\n", pid2jid(pid), pid, WSTOPSIG(status));
// //             pjob = getjobpid(jobs, pid);
// //             pjob->state = ST;
// //         }
// //     }
// //     sigprocmask(SIG_SETMASK, &prev_mask, NULL);
// //     errno = oldErrno;
// //     free(pjob);
// //     return;
// // }

// /* 
//  * sigint_handler - The kernel sends a SIGINT to the shell whenver the
//  *    user types ctrl-c at the keyboard.  Catch it and send it along
//  *    to the foreground job.  
//  */
// void sigint_handler(int sig) 
// {
//     sigset_t mask, prev_mask;
//     sigfillset(&mask);
//     int oldErrno = errno;
//     //访问jobs之前阻塞所有信号
//     sigprocmask(SIG_BLOCK, &mask, &prev_mask);
//     pid_t target_pid = fgpid(jobs);
//     sigprocmask(SIG_SETMASK, &prev_mask, NULL);
//     if(target_pid!=0)
//     {
//         if(kill(-target_pid, SIGINT)<0)
//             unix_error("Kill Error\n");
//     }
//     errno = oldErrno;
//     return;
// }

// /*
//  * sigtstp_handler - The kernel sends a SIGTSTP to the shell whenever
//  *     the user types ctrl-z at the keyboard. Catch it and suspend the
//  *     foreground job by sending it a SIGTSTP.  
//  */
// // void sigtstp_handler(int sig) 
// // {
// //     sigset_t mask, prev_mask;
// //     sigfillset(&mask);
// //     int oldErrno = errno;
// //     sigprocmask(SIG_BLOCK, &mask, &prev_mask);
// //     pid_t target_pid = fgpid(jobs);
// //     sigprocmask(SIG_BLOCK, &prev_mask, NULL);
// //     if(target_pid!=0)
// //     {
// //         if(kill(-target_pid, SIGTSTP)<0)
// //             unix_error("Kill Error\n");
// //     }
// //     errno = oldErrno;
// //     return;
// // }
// void sigtstp_handler(int sig) 
// {
//     int olderrno = errno;
//     sigset_t mask_all,prev_all;
//     pid_t pid;
//     struct job_t *curr_job;
//     sigfillset(&mask_all);
//     sigprocmask(SIG_BLOCK,&mask_all,&prev_all);
//     pid=fgpid(jobs);
//     if(pid){
//         //curr_job=getjobpid(jobs,pid);
//         //curr_job->state=ST;   
//         kill(-pid,SIGTSTP);
//         //这一步很关键，此时waitfg还在等待前台进程回收，但是此时已经有个stop信号过来了
//         //此时前台进程被终止，但是shell会接受新的命令
//         //因此要让waitfg结束  
//         //printf("Job [%d] (%d) stopped by signal 20\n", curr_job->jid, curr_job->pid);
//     }  
//     sigprocmask(SIG_SETMASK,&prev_all,NULL);
//     errno = olderrno;
//     return;
// }

/* 
 * sigchld_handler - The kernel sends a SIGCHLD to the shell whenever
 *     a child job terminates (becomes a zombie), or stops because it
 *     received a SIGSTOP or SIGTSTP signal. The handler reaps all
 *     available zombie children, but doesn't wait for any other
 *     currently running children to terminate.  
 */
void sigchld_handler(int sig) 
{
    int olderrno = errno;
    pid_t pid;
    sigset_t mask_all,prev_all;
    sigfillset(&mask_all);
    int status;
 
    while ((pid=waitpid(-1, &status, WNOHANG|WUNTRACED))>0)
    {
        sigprocmask(SIG_BLOCK, &mask_all, &prev_all);
        //防止出现该进程不是被父进程杀死，如果不加WUNTRACED标志位，就会出现不执行sigchld_handler这一函数
        //但是jobs中一直没有删除这个job，如果是前台运行的程序，就会一直等待
        if (WIFEXITED(status))//该进程正常结束
            deletejob(jobs,pid);
        else if(WIFSTOPPED(status)){//可以监听到只要该进程接收到停止信号
            getjobpid(jobs,pid)->state = ST;
            printf("Job [%d] (%d) stopped by signal 20\n", pid2jid(pid), pid);
        }
        else if (WIFSIGNALED(status)){//该进程被信号杀死
            printf("Job [%d] (%d) terminated by signal 2\n", pid2jid(pid), pid);  
            deletejob(jobs,pid);
        }
        sigprocmask(SIG_SETMASK, &prev_all, NULL);
    }
    /*当waitpid第一个参数为-1,并且第三个参数设置为0，也就是阻塞等待时，我理解这个错误码的意思是没有可回收的子进程了，
    *我理解这里需要等待所有在执行子进程都要被回收
    *所以如果所有可回收的子进程已经回收，那么错误码一定是这个，如果是其他的则说明这个是错误的
    *但是当设置为非阻塞时，就不需要了，因为此时很有可能仍然有子进程在执行，所以errno不一定为ECHILD
    *ECHILD错误码官方解释只有在第一个参数为pid时，解释为如果这个子进程被回收，就会出现这个错误码，
    *所以我觉得如果填-1，就是回收所有子进程才会出现这个错误码
    */
    //if (errno != ECHILD)
    //    printf("waitpid error\n");
    errno=olderrno;
    return;
}
 
/* 
 * sigint_handler - The kernel sends a SIGINT to the shell whenver the
 *    user types ctrl-c at the keyboard.  Catch it and send it along
 *    to the foreground job.  
 * 如果接受到SIGINT信号，就会杀死前台进程所在的进程组中的所有进程，实现就是靠kill函数，并且第一个参数为负数
 */
void sigint_handler(int sig) 
{
    pid_t fgid=fgpid(jobs);
    kill(-fgid, sig);                                                                                                                                         
    return;
}
 
/*
 * sigtstp_handler - The kernel sends a SIGTSTP to the shell whenever
 *     the user types ctrl-z at the keyboard. Catch it and suspend the
 *     foreground job by sending it a SIGTSTP.  
 */
void sigtstp_handler(int sig) 
{
    pid_t fgid=fgpid(jobs);
    kill(-fgid, sig); 
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

    for (i = 0; i < MAXJOBS; i++)
	if (jobs[i].state == FG)
	    return jobs[i].pid;
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
    for (i = 0; i < MAXJOBS; i++)
	if (jobs[i].pid == pid) {
            return jobs[i].jid;
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




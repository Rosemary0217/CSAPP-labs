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
extern char **environ;      /* defined in libc 在execv函数中用到了（应该是本机的环境变量，可以借鉴）*/
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
    /*个人理解是，将文件描述符2（原来是标准错误输出）重定位到文件描述符1（标准输出），
     *也就是所有的输出信息都是通过stdout，这样只有通过stdout就可以把所有信息输出出来（？？？暂时这样理解）*/
    dup2(1, 2);
 
    /* Parse the command line */
    /* 在运行./tsh时,可以在./tsh后面加-h或者-v或者-p，可以实现不同的功能*/
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
    //个人理解job结构体就是一个执行命令的子进程，jobs就是存放已有的执行任务信息的数组
    initjobs(jobs);
 
    /* Execute the shell's read/eval loop */
    while (1) {
 
	/* Read command line */
	if (emit_prompt) {
	    printf("%s", prompt);
	    fflush(stdout);//这个函数是清除输入的缓存
	}
    //检查输入命令接收是否成功，输入是否有问题
	if ((fgets(cmdline, MAXLINE, stdin) == NULL) && ferror(stdin))
	    app_error("fgets error");
	if (feof(stdin)) { /* End of file (ctrl-d)，检测标准输入是否有结束符，只有按ctrl+d时，输入一个EOF符，就会终止 */
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
 
/* 
 * parseline - Parse the command line and build the argv array.
 * 
 * Characters enclosed in single quotes are treated as a single
 * argument.  Return true if the user has requested a BG job, false if
 * the user has requested a FG job. 
 * 一方面可以判断cmdline是后台还是前台工作，另一方面也可以将cmdline切分成argv数组 
 */
int parseline(const char *cmdline, char **argv) 
{
    static char array[MAXLINE]; /* holds local copy of command line */
    char *buf = array;          /* ptr that traverses command line */
    char *delim;                /* points to first space delimiter */
    int argc;                   /* number of args */
    int bg;                     /* background job? */
 
    strcpy(buf, cmdline);
    buf[strlen(buf)-1] = ' ';  /* replace trailing '\n' with space 将\n符变成空格 */
    while (*buf && (*buf == ' ')) /* ignore leading spaces 忽视命令开始的空格*/
	buf++;
 
    /* Build the argv list 建立argv数组*/
    /*
    *以一个例子详细说明，假设cmdline="/bin/ls -a"
    *在1处是进行预处理，将开始的空格去除，并且delim定位到第一处分隔符处，在例子中也就是cmdline[8]（ls后面的空格）
    *在2处，注意argv[0]是一个字符串指针，指向buf指向的地址，
    *在第一次循环时指向cmdline[0],此时printf(argv[0])结果是“/bin/ls -a”然后把delim变为\0。也就是把cmdline[8]变为终止符，此时printf(argv[0])结果是“/bin/ls”,这样就通过空格分开了命令
    */
    //1
    argc = 0;
    if (*buf == '\'') {
	buf++;
	delim = strchr(buf, '\'');
    }
    else {
	delim = strchr(buf, ' ');
    }
 
    while (delim) {
        //2
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
 * it immediately.  
 */
int builtin_cmd(char **argv) 
{
    if (!strcmp(argv[0],"quit"))
        exit(0);
    else if (!strcmp(argv[0],"jobs")){
        listjobs(jobs);
        return 1;
    }
    else if (!strcmp(argv[0],"bg")||!strcmp(argv[0],"fg"))
    {
        do_bgfg(argv);
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
 
/* 
 * waitfg - Block until process pid is no longer the foreground process
 */
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
 * 开启signum的信号捕获，handler是信号捕获后的处理函数，返回的是上一个处理函数（没什么用）
 */
handler_t *Signal(int signum, handler_t *handler) 
{
    struct sigaction action, old_action;
 
    action.sa_handler = handler;  //设置信号执行函数
    sigemptyset(&action.sa_mask); /* block sigs of type being handled */
    action.sa_flags = SA_RESTART; /* restart syscalls if possible */
                                  /*如果信号打断了系统调用，就会重新启动原来的系统调用，一般会被信号打断的系统调用有读写终端，网络，磁盘，wait，pause等 */
 
    if (sigaction(signum, &action, &old_action) < 0)
	unix_error("Signal error");
    return (old_action.sa_handler);//返回的是旧的处理方式
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
 
 
 
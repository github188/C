#include <stdio.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <sys/user.h> 
#include <sys/reg.h>  /* For constants ORIG_EAX etc */

#include "siid.h"

/* Notice: 
 *       system interrupt number can be found on /usr/include/asm/unistd.h
 *       for X86_64 is on  /usr/include/asm/unistd_64.h
 *       for X86_32 is on  /usr/include/asm/unistd_32.h
 */

int main(int argc, char* argv[])
{   
	int flag;
	long int ret;
	long int syscallID;
	int val;
	pid_t pid;

	/* 32 bit , sizeof long is 4 */
	/* 64 bit , sizeof long is 8 */
	int offset = sizeof(long);

	switch(pid = fork())
    {
    case -1:
        return -1;
    case 0: /* child process */
        ptrace(PTRACE_TRACEME,0,NULL,NULL);
        execl("./hello", "hello", NULL);
    default: /* parent process */
        wait(&val); /* wait for execl */
        if(WIFEXITED(val))
            return 0;
#ifdef __x86_64__
        syscallID=ptrace(PTRACE_PEEKUSER, pid, ORIG_RAX*offset, NULL);
#else
        syscallID=ptrace(PTRACE_PEEKUSER, pid, ORIG_EAX*offset, NULL);
#endif
        printf("Process executed system call ID = %-3ld (%-10s)\n",syscallID, siid[syscallID]);
        ptrace(PTRACE_SYSCALL,pid,NULL,NULL);
        while(1)
        {
            wait(&val); /* wait signal */
            if(WIFEXITED(val)) /* check if child exit */
			{
				printf("\nchild process exit\n");
                return 0;
			}
            if(flag==0) //第一次(进入系统调用)，获取系统调用的参数
            {
#ifdef __x86_64__
                syscallID=ptrace(PTRACE_PEEKUSER, pid, ORIG_RAX*offset, NULL);
#else
                syscallID=ptrace(PTRACE_PEEKUSER, pid, ORIG_EAX*offset, NULL);
#endif
                printf("Process executed system call ID = %-3ld (%-10s) ",syscallID, siid[syscallID]);
                flag=1;
            }
            else //第二次(退出系统调用)，获取系统调用的返回值
            {
#ifdef __x86_64__
                ret=ptrace(PTRACE_PEEKUSER, pid, RAX*offset, NULL);
#else
                ret=ptrace(PTRACE_PEEKUSER, pid, EAX*offset, NULL);
#endif
                printf("with return value= %ld\n", ret);
                flag=0;
            }
            ptrace(PTRACE_SYSCALL,pid,NULL,NULL);
        }
    }

	printf("\n");
    return 0;
}


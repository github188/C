#include <stdio.h>  
#include <stdlib.h>  
#include <unistd.h>  

#include "setproctitle.h"

char **os_argv;
int test(int argc,char **argv)
{
	os_argv = argv;

	if (0 != init_setproctitle()) {
		printf("Fail to do init_setproctitle\n");
	}

	/*here use test: as mark for this program */
	setproctitle("test: master process");

	int i=0;
	pid_t pid;
	for (i=0; i<4; i++) {
		if ((pid = fork()) == -1) {
			perror("Failed to fork process.\n");
			exit(1);
		} else if (pid == 0) {      /* child process */
			char buf[100] = {0};
			printf("test: fork process %d\n", i+1);
			snprintf(buf, sizeof(buf), "test: worker procee %d", i+1);
			setproctitle(buf);
			sleep(30);
			return(0);
		} 
	}
	
	sleep(30);

	return 0;
}

int main(int argc,char **argv)
{
	test(argc, argv);
	return 0;
}


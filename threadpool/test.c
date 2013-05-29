/**
 * test.c
 * sample code of thread pool
 */

#include <stdio.h>
#include "thread_pool.h"

thrdpool_t *g_pthreadpool = NULL;

typedef void* (*task)(void*);


void* Task1(void *arg)
{
	ENTER_FUNC();
	//printf("parameter: %d\n", *((int*)arg));
	int i=100;
	while (i--) {
		printf("This is %s\n", __func__);
		sleep(1);
	}
	EXIT_FUNC();
	return 0;
}

void* Task2(void *arg)
{
	ENTER_FUNC();
	//printf("parameter: %d\n", *(int*)arg);
	int i=50;
	while (i--) {
		printf("This is %s\n", __func__);
		sleep(2);
	}
	EXIT_FUNC();
	return 0;
}

int InitPool()
{
	char logfile[256] = {0};

	g_pthreadpool = thr_createThrdPool(10, 20, logfile);
	return (g_pthreadpool == NULL) ? 1 : 0;
}

void AddTask(task func_ins, void *arg_ins, task func_exit, void *arg_exit)
{
	thrdcall_t thrdcall_ins,thrdcall_exit;
	thrdcall_ins.arg=arg_ins;
	thrdcall_ins.thrdfunc=func_ins;
	thrdcall_exit.arg=arg_exit;
	thrdcall_exit.thrdfunc=func_exit;
	thr_add_task(g_pthreadpool, 1, thrdcall_ins, thrdcall_exit);
}

int main(int argc, char **argv)
{
	if (0 != InitPool()) return 1;

	int arg_ins=1;
	float arg_exit=7;
	AddTask(Task1, &arg_ins, NULL, &arg_exit);
	AddTask(Task2, &arg_ins, NULL, &arg_exit);

	while(1) {
		sleep(10);
	}

	return 0;
}

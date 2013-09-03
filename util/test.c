/*
 * Test for utility function
 * 
 * Compile:
 *        gcc -o test test.c util.c
 *
 * History:
 *        2013-04-28 Dennis Create
 *
 */

#include <stdio.h>
#include "util.h"

int main(int argc, const char *argv[])
{
	/* generate a array with 30 elements, and do hex dump */
	unsigned int t_arr_t[30] = {0};
	get_random_bytes(t_arr_t, sizeof(t_arr_t));
	lamont_hdump((unsigned char*)t_arr_t, sizeof(t_arr_t));

	/* check interval time */
	static int work_time = 0;
	#define WORK_INTERVAL_TIME 5
	if (1 == check_work_time(&work_time, WORK_INTERVAL_TIME)) {
		printf("time to do job.\n");
	}
	else {
		printf("free time.\n");
	}
	sleep(3);
	if (1 == check_work_time(&work_time, WORK_INTERVAL_TIME)) {
		printf("time to do job.\n");
	}
	else {
		printf("free time.\n");
	}
	sleep(3);
	if (1 == check_work_time(&work_time, WORK_INTERVAL_TIME)) {
		printf("time to do job.\n");
	}
	else {
		printf("free time.\n");
	}
	sleep(2);
	if (1 == check_work_time(&work_time, WORK_INTERVAL_TIME)) {
		printf("time to do job.\n");
	}
	else {
		printf("free time.\n");
	}

	return 0;
}

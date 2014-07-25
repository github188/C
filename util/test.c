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
#include <stdlib.h>
#include "util.h"
#include "time_test.h"

int main(int argc, const char *argv[])
{
	/* generate a array with 30 elements, and do hex dump */
	unsigned int t_arr_t[30] = {0};
	get_random_bytes(t_arr_t, sizeof(t_arr_t));
	lamont_hdump((char*)t_arr_t, sizeof(t_arr_t));

	/* check interval time */
#if 0
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
#endif

#if 0
#define PRINT(a) printf(#a"=%d\n", a)
	int a = 5;
	int b = 3;
	PRINT(a);
	PRINT(b);
	SWAP(a,b);
	PRINT(a);
	PRINT(b);
#endif

	/* splits string to array */
	int i=0;
	char results[50][MAX_STR_LEN] = {};
	/*
	char *test = "";
	char *test = "  ";
	char *test = "abc 123   55 66 a12cc";
	*/
	char *test = "  abc 123   55 66 a12cc  ";

	int count = get_buffer_all(test, ' ', results, sizeof(results));
	for (i=0; i<count; i++)
		printf("results[%d] = %s\n", i, results[i]);

	
	TIME_START();
	system("ls");
	TIME_END();

	return 0;
}

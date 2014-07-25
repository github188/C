#ifndef _TIME_TEST_
#define _TIME_TEST_

#include <time.h>      /* clock */
#include <sys/time.h>  /* gettimeofday */

/* NOTICE! Change here to select the method you want */
#define USE_CLOCK 0

/* Using clock, calculate CPU time, cpu_time=user_time+sys_time */
clock_t _ct_start, _ct_end;
#define TIME_START_CL() do { _ct_start = clock();} while (0)
#define TIME_END_CL()  do { _ct_end = clock(); \
	printf("Elapsed time %ld sec\n", (_ct_end - _ct_start)/CLOCKS_PER_SEC); \
/*	printf("Elapsed time %ld usec\n", (_ct_end - _ct_start)/(CLOCKS_PER_SEC/1000000)); \ */ \
	} while (0)

/* Using gettimeofday, calculate real time, real_time=cpu_time+wait_time
 * Because linux is multi-task operate system, so the value of wait_time is 
 * difference on each task
 */
struct timeval _tv_begin, _tv_end;
#define TIME_START_TV() do { gettimeofday(&_tv_begin, NULL); } while (0)
#define TIME_END_TV()   do { gettimeofday(&_tv_end, NULL); \
		printf("Elapsed time %ld usec\n", _tv_end.tv_usec - _tv_begin.tv_usec); \
		} while (0)

#if USE_CLOCK
	#define TIME_START() TIME_START_CL()
	#define TIME_END()   TIME_END_CL()
#else
	#define TIME_START() TIME_START_TV()
	#define TIME_END()   TIME_END_TV()
#endif 

/* 
Sample code:

#include "time_test.h"

int main(int argc, char *argv[]) {
	TIME_SATRT();
	// DO YOUR JOB HERE
	TIME_END();
	return 0;
}
*/

#endif /* _TIME_TEST_ */

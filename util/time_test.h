#ifndef _TIME_TEST_
#define _TIME_TEST_

#include <time.h>
#include <sys/time.h>

/* NOTICE! Change here to select the method you want */
#define USE_CLOCK 1

/* Using clock, calculate CPU time */
clock_t _ct_start, _ct_end;
#define TIME_START_CL() do { _ct_start = clock();} while (0)
#define TIME_END_CL()  do { _ct_end = clock(); \
	printf("time = %ld\n", _ct_end - _ct_start); } while (0)

/* Using gettimeofday, calculate real time */
struct timeval _tv_begin, _tv_end;
#define TIME_START_TV() do { gettimeofday(&_tv_begin, NULL); \
		printf("sec=%d, usec=%d\n",_tv_begin.tv_sec, _tv_begin.tv_usec); } while (0)
#define TIME_END_TV()   do { gettimeofday(&_tv_end, NULL); \
		printf("sec=%d, usec=%d\n",_tv_end.tv_sec, _tv_end.tv_usec); \
		printf("time = %d\n", _tv_end.tv_usec - _tv_begin.tv_usec); } while (0)

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

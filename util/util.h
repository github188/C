#ifndef _UTIL_H_
#define _UTIL_H_

void lamont_hdump(char *cp, unsigned int length);
int get_random_bytes(void *buf, int numbytes);
int check_work_time(long *work_time, const int interval_time);

#endif


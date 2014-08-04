#ifndef _UTIL_H_
#define _UTIL_H_

#define MAX_STR_LEN 255

#define SWAP(a,b) {a=a^b; a=a^b; a=a^b;}

void lamont_hdump(char *cp, unsigned int length);
int get_random_bytes(void *buf, int numbytes);
int check_work_time(long *work_time, const int interval_time);
void print_buf(char *buf, int len);
void print_buf2(char *buf, int len);
int get_buffer_all(const char *buffer, const char delim, char (*results)[MAX_STR_LEN], const int size);

#endif


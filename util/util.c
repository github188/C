#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/time.h>
#include <time.h> 
#include "util.h"

/*
 * code from nmap 3.20
 * function:
 *    1. hex dump
 *    2. generate random data
 */

/* A better version of hdump, from Lamont Granquist.  Modified slightly
   by Fyodor (fyodor@insecure.org) */
void lamont_hdump(char *cp, unsigned int length) {

	/* stolen from tcpdump, then kludged extensively */

	static const char asciify[] = "................................ !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~.................................................................................................................................";

	const u_short *sp;
	const u_char *ap;
	unsigned char *bp = (unsigned char *) cp;
	u_int i, j;
	int nshorts, nshorts2;
	int padding;

	printf("\n\t");
	padding = 0;
	sp = (u_short *)bp;
	ap = (u_char *)bp;
	nshorts = (u_int) length / sizeof(u_short);
	nshorts2 = (u_int) length / sizeof(u_short);
	i = 0;
	j = 0;
	while(1) {
		while (--nshorts >= 0) {
			printf(" %04x", ntohs(*sp));
			sp++;
			if ((++i % 8) == 0)
				break;
		}
		if (nshorts < 0) {
			if ((length & 1) && (((i-1) % 8) != 0)) {
				printf(" %02x  ", *(u_char *)sp);
				padding++;
			}
			nshorts = (8 - (nshorts2 - nshorts));
			while(--nshorts >= 0) {
				printf("     ");
			}
			if (!padding) printf("     ");
		}
		printf("  ");

		while (--nshorts2 >= 0) {
			printf("%c%c", asciify[*ap], asciify[*(ap+1)]);
			ap += 2;
			if ((++j % 8) == 0) {
				printf("\n\t");
				break;
			}
		}
		if (nshorts2 < 0) {
			if ((length & 1) && (((j-1) % 8) != 0)) {
				printf("%c", asciify[*ap]);
			}
			break;
		}
	}
	if ((length & 1) && (((i-1) % 8) == 0)) {
		printf(" %02x", *(u_char *)sp);
		printf("                                       %c", asciify[*ap]);
	}
	printf("\n");
}

int get_random_bytes(void *buf, int numbytes) {
	static char bytebuf[2048];
	static char badrandomwarning = 0;
	static int bytesleft = 0;
	int res;
	int tmp;
	struct timeval tv;
	FILE *fp = NULL;
	unsigned int i;
	short *iptr;

	if (numbytes < 0 || numbytes > 0xFFFF) return -1;

	if (bytesleft == 0) {
		fp = fopen("/dev/arandom", "r");
		if (!fp) fp = fopen("/dev/urandom", "r");
		if (!fp) fp = fopen("/dev/random", "r");
		if (fp) {
			res = fread(bytebuf, 1, sizeof(bytebuf), fp);
			if (res != sizeof(bytebuf)) {    
				error("Failed to read from /dev/urandom or /dev/random");
				fclose(fp);
				fp = NULL;
			}      
			bytesleft = sizeof(bytebuf);
		}
		if (!fp) {  
			if (badrandomwarning == 0) {
				badrandomwarning++;
				/*      error("WARNING: your system apparently does not offer /dev/urandom or /dev/random.  Reverting to less secure version."); */

				/* Seed our random generator */
				gettimeofday(&tv, NULL);
				srand((tv.tv_sec ^ tv.tv_usec) ^ getpid());
			}

			for(i=0; i < sizeof(bytebuf) / sizeof(short); i++) {
				iptr = (short *) ((char *)bytebuf + i * sizeof(short));
				*iptr = rand();
			}
			bytesleft = (sizeof(bytebuf) / sizeof(short)) * sizeof(short);
			/*    ^^^^^^^^^^^^^^^not as meaningless as it looks  */
		} else fclose(fp);
	}

	if (numbytes <= bytesleft) { /* we can cover it */
		memcpy(buf, bytebuf + (sizeof(bytebuf) - bytesleft), numbytes);
		bytesleft -= numbytes;
		return 0;
	}

	/* We don't have enough */
	memcpy(buf, bytebuf + (sizeof(bytebuf) - bytesleft), bytesleft);
	tmp = bytesleft;
	bytesleft = 0;
	return get_random_bytes((char *)buf + tmp, numbytes - tmp);
}

/*
 * Func: check work time
 * Para:
 *       work_time      work time, unit: microsecond
 *       interval_time  interval time, unit: second 
 * Ret : 
 *       if cur_time - work_time > interval_time, return 1
 *       else return 0
 */
int check_work_time(long *work_time, const int interval_time)
{
	long cur_time;
	struct timeval t_cur; 

	gettimeofday(&t_cur, NULL); 
	cur_time = ((long)t_cur.tv_sec)*1000 + (long)t_cur.tv_usec/1000; 

	if ( (cur_time - *work_time) > interval_time*1000 ) {
		*work_time = cur_time;
		return 1;
	}

	return 0;
}

/*
 * print buffer
 */
void print_buf(char *buf, int len)
{
	printf("\n---------------data buf: %d bytes----------------", len);
	int i=0;
	for (; i<len; i++) {
		if (i%16 == 0) printf("\n");
		else if (i%8 == 0) printf("  ");
		printf("%02x ", buf[i]&0xff); /* avoid integer type-promotion */
	}
	printf("\n-------------------------------------------------\n\n");
}

/*
 * splite buffer to array by delim character
 */
int get_buffer_all(const char *buffer, const char delim, char (*results)[MAX_STR_LEN], const int size)
{
	const char *pos1, *pos2;
	int num = 0;

	pos1 = pos2 = buffer;

	while (1) {
		/* find position of not delim character */
		while (*pos1 == delim) pos1++;

		/* find position of delim character or terminal */
		pos2 = pos1;
		while (*pos2 != delim && *pos2 != '\0') pos2++;

		if (pos2 == pos1 || num == size) break;

		strncpy(results[num++], pos1, (int)(pos2-pos1));

		if (*pos2 == '\0') break;
		pos1 = pos2;
	}

	return num;
}


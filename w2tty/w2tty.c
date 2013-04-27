/*
 * Broadcast message to all terminal
 *
 * Compile: gcc -o w2tty w2tty.c dowall.c
 *
 * Usage: ./w2tty message
 *
 * History:
 *        2013-04-27 Dennis Create
 *
 * Note:
 *     1. dowall.c is downloaded from 
 *        http://ftp.slackware.com/pub/archlinux/core/os/i686/sysvinit-tools-2.88-9-i686.pkg.tar.xz 
 *     2. I modify the line length from 81 to 91.(File:dowell.c Line:159)
 *     3. System command "wall" have the same function.
 *        example like this:  "wall testmessage" 
 */

#include <stdio.h>
#include <string.h>
#include "dowall.h"

#define MAXLEN 1024

int main(int argc, const char *argv[])
{
	int i=0;
	char buf[MAXLEN] = {0};
	memset(buf, 0, sizeof(buf));

	strcat(buf, "\r\n\r\n");

	int len=0;
	for (i = 1; i < argc; i++) {
		len += strlen(argv[i]) + 1;
		if (len > MAXLEN) break;
		strcat(buf, argv[i]);
		strcat(buf, " ");
	}
	strcat(buf, "\r\n");

	wall(buf, 0);

	return 0;
}

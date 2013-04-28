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

	return 0;
}

/*
 * Copyleft(c) 2012-2013 
 * Authored by Dennis on: Mon Apr  1 23:51:12 CST 2013
 * @Desc:
 *      Test for trim bank
 * @History
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 128

// trim begin and end space
void trim_bank(char* buf)
{
	int a=0;
	int b=0;
	int len=0;

	if (!buf) return;

	len=strlen(buf);
	while (a<len && isspace(buf[a++]));
	// do with "   ", only bank in the string
	if (a--==len) {
		memset(buf, 0, len);
		return;
	}

	b=len;
	while (b>=0 && isspace(buf[--b]));
	b++;

	strncpy(buf, buf+a, b-a);
	buf[b-a] = '\0';
	memset(buf+b-a, 0, len-b+a);
}

void print_arr(char* buf, int size)
{
	printf(" array characters:\"");
	int i=0;
	for (i=0; i<size; i++)
		printf("%c", buf[i]);
	printf("\"\n");
}

void testFunc(char* buf)
{
	char arr[MAX_SIZE] = {0};

	memset(arr, 0, sizeof(arr));
	strncpy(arr, buf, sizeof(arr));
	
	printf("Before trim bank, Len:%d,\"%s\"\n", strlen(arr), arr);
	trim_bank(arr);
	printf(" After trim bank, Len:%d,\"%s\"\n", strlen(arr), arr);
	print_arr(arr, sizeof(arr));
}

int main(int argc, char* argv[])
{
	// Test case
	testFunc("");
	testFunc("   ");
	testFunc("abc 1234");
	testFunc("abc 1234  ");
	testFunc("  abc 1234");
	testFunc("  abc 1234  ");

	// Test for null point
	char* p;
	trim_bank(p);

	return 0;
}

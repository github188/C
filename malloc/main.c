#include <stdio.h>
#include <string.h>
#include "mm.h"

int main(int argc, char* argv[])
{
	char *p = mm_malloc(10);
	if (p == NULL) 
	{
		printf("Failed to allocate memory.\n");
		return 0;
	}	

	memset(p, '\0', 10);

	strcpy(p, "hello world");

	printf("p = %s\n", p);

	mm_free(p);

	return 0;
}


#include <stdio.h>
#include <string.h>
#include "mm.h"

#define GO_HERE() printf("%s %d\n", __func__, __LINE__)

int main(int argc, char* argv[])
{
	int i;
	GO_HERE();
	int *p = (int *)mm_malloc(10);
	GO_HERE();
	if (p == NULL) 
	{
		printf("Failed to allocate memory.\n");
		return 0;
	}	

	for (i=0; i<10; i++)
		p[i] = i;

	for (i=0; i<10; i++)
		printf("%d\n", p[i]);

	mm_free(p);

	return 0;
}


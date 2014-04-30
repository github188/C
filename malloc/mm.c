#include <sys/types.h>
#include <unistd.h>

struct header_block {
	int size;
};

void* mm_malloc(unsigned int size)
{
	return NULL;
}

void  mm_free(void *p)
{
}

/* A simple version */
#include <sys/types.h>
#include <unistd.h>
void *malloc_version0(size_t size)
{
    void *p;
    p = sbrk(0);
    if (sbrk(size) == (void*)-1)
        return NULL;
    return p;
}

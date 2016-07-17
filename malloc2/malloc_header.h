#ifndef MALLOC_HEADER_H
#define MALLOC_HEADER_H

#include <sys/types.h>

void* malloc_version0(size_t size);
void* malloc_version1(size_t size);
void* malloc_version2(size_t size);

#endif // MALLOC_HEADER_H

#include <iostream>
#include <sys/time.h> // for gettimeofday()
#include <stdlib.h> // for malloc
#include <string.h> // for memcpy
#include "rdtsc.h"
using namespace std;

typedef unsigned int uint32;

#define RDTSC 1
#ifdef RDTSC

// cat /proc/cpuinfo |grep 'MHz'
#define CPUMHZ 1200.0f
// frequency per micro second
#define CPU_SPEED_US (CPUMHZ*1024*1024/1000/1000)
unsigned long long t;
#define TIME_START() t = rdtsc();
#define TIME_END() do { \
    t = rdtsc() - t; \
    cout << __FUNCTION__ << ", cost " << t << " cycles, times " << count \
        << ", average " << t/count << " cycle\n"; \
} while (0)
#else

struct timeval t1, t2;
#define TIME_START() gettimeofday(&t1, NULL)
#define TIME_END() do { \
    gettimeofday(&t2, NULL); \
    double elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000000.0; \
    elapsedTime += (t2.tv_usec - t1.tv_usec); \
    cout << __FUNCTION__ << ", cost " << elapsedTime << " us, times " << count \
        << ", average " << elapsedTime/count << " us\n"; \
} while (0)

#endif

void test_assign()
{
    uint32 tmp = 0;
    uint32 count = 10000*100;
    TIME_START();
    for (uint32 i=0; i<count; i++)
    {
        tmp = i;
    }
    TIME_END();
}

void test_memcpy()
{
    char tmp1[1024] = {0};
    char tmp2[1024] = {'a'};
    uint32 count = 10000;
    TIME_START();
    for (int i=0; i<count; i++) {
        memcpy(tmp1, tmp2, sizeof(tmp1));
    }
    TIME_END();
}

void test_allocate_memory_from_stack()
{
    uint32 count = 10000 * 10;
    TIME_START();
    for (int i=0; i<count; i++) {
        char arr[1024]; // allocate memory from stack
    }
    TIME_END();
}

void _test_malloc(uint32 size)
{
    cout << "malloc size " << size << " ";
    uint32 count = 1;
    TIME_START();
    char* tmp = (char*)malloc(size); // allocate memory from heap
    TIME_END();
    if (tmp) free(tmp);
}

void test_malloc()
{
    _test_malloc(100);
    _test_malloc(1000);
    _test_malloc(1024);       // 1KB
    _test_malloc(1024*10);
    _test_malloc(1024*100);
    _test_malloc(1024*1024);  // 1MB
}

void _func(int a, int b, const char* p)
{
    // do nothing
}

void test_function_called()
{
    const char* tmp = "123";
    uint32 count = 10000 * 100;
    TIME_START();
    for (uint32 i=0; i<count; i++)
    {
        _func(i, i, tmp);
    }
    TIME_END();
}

void test_lock()
{
    uint32 count = 1;
    TIME_START();
    // TODO
    TIME_END();
}

void test_signal()
{
    uint32 count = 1;
    TIME_START();
    // TODO
    TIME_END();
}

void test_mutex()
{
    uint32 count = 1;
    TIME_START();
    // TODO
    TIME_END();
}

void test_message_queue()
{
    uint32 count = 1;
    TIME_START();
    // TODO
    TIME_END();
}

void test_quick_sort()
{
    uint32 count = 1;
    TIME_START();
    // TODO
    TIME_END();
}

void test_io_read()
{
    uint32 count = 1;
    TIME_START();
    // TODO
    TIME_END();
}

void test_io_write()
{
    uint32 count = 1;
    TIME_START();
    // TODO
    TIME_END();
}

void test_network_write()
{
    uint32 count = 1;
    TIME_START();
    // TODO
    TIME_END();
}

void test_network_read()
{
    uint32 count = 1;
    TIME_START();
    // TODO
    TIME_END();
}

int main()
{
    test_assign();
    test_memcpy();
    test_malloc();
    test_allocate_memory_from_stack();
    test_function_called();

    return 0;
}

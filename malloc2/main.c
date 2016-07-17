#include <stdio.h>
#include "malloc_header.h"

#define ASSERT_TRUE(exp) do { \
    if (!(exp)) { \
        printf("%s:%d, %s failed\n", __FILE__, __LINE__, #exp); \
    } \
} while (0)

void test_version0()
{
    char* p = malloc_version0(100);
    ASSERT_TRUE(p != NULL);
}

void test_version1()
{

}

int main(int argc, char* argv[])
{
    test_version0();
    test_version1();
    return 0;
}

// common.h
#ifndef _COMMON_H_
#define _COMMON_H_

#include "commdef.h"

void print_msg(struct bcast_msg msg);
#define DDEBUG {printf("File:%s Func:%s Line:%d\n", __FILE__, __FUNCTION__, __LINE__);}

#endif

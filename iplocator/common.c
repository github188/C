#include "common.h"

void print_msg(struct bcast_msg msg)
{
	printf("id:%s\n", msg.id);
	printf("type:%d\n", msg.type);
	printf("function:%d\n", msg.function);
	printf("dev:%c\n", msg.devinfo.dev);
	printf("name:%s\n", msg.devinfo.name);
	printf("ifname:%s\n", msg.devinfo.ifname);
	printf("ip:%s\n", msg.devinfo.ip);
	printf("mac:%s\n", msg.devinfo.mac);
}

/*
 * netdetect.c
 *
 * Detech ethernet interface plugged status
 * 
 * @history:
 *        2013-04-25 Dennis Create
 */

/* Reference: http://www.cnblogs.com/sunzl1987/archive/2012/05/24/2516635.html */

#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/if.h>
#include <string.h>
#include <stdio.h>

int net_detect(const char* net_name) {
    int skfd = 0;
    struct ifreq ifr;

	if (strlen(net_name) > IFNAMSIZ) {
		printf("Length of ethernet interface is too long. The limit len is %d.\n", IFNAMSIZ);
		return 1;
	}

    skfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(skfd < 0) {
        printf("Failed to open socket!\n");
        return 1;
    }

    strcpy(ifr.ifr_name, net_name);
    if(ioctl(skfd, SIOCGIFFLAGS, &ifr) < 0 ) {
        printf("Maybe ethernet inferface %s is not valid!\n", net_name);
        close(skfd);
        return 1;
    }

    close(skfd);

    if(ifr.ifr_flags & IFF_RUNNING) {
        printf("%s is running.\n", net_name);
		return 0;
    }

	printf("%s is not running.\n", net_name);
    return 1;
}

void usage(const char* prog) {
	printf("Usage  : %s interface\n", prog);
	printf("\treturn 0 if interface is running, else 1. ");
	printf("Get the output msg for detail.\n");
	printf("Example: \n", prog);
	printf("         %s eth0\n", prog);
}

int main(int argc, const char *argv[]) {
	if (argc < 2) {
		usage(argv[0]);
		return 1;
	}

    return net_detect(argv[1]);
}

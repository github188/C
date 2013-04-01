#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <netdb.h>
#include <sys/ioctl.h>
#include <net/if.h>

#include "commdef.h"
#include "common.h"

int main(int argc,char*argv[]) {
	int ret=-1;
	int sock=-1;
	int so_broadcast=1;
	struct sockaddr_in broadcast_addr;
	struct sockaddr_in from_addr;
	int from_len=sizeof(from_addr);
	int count=-1;
	fd_set readfd;

	struct bcast_msg sendmsg;
	struct bcast_msg recvmsg;
	strncpy(sendmsg.id, BCAST_ASK, sizeof(sendmsg.id));
	sendmsg.type = 1;
	sendmsg.function = 1;
	memset(&(sendmsg.devinfo), 0, sizeof(sendmsg.devinfo));

	struct timeval timeout;
	timeout.tv_sec=2;
	timeout.tv_usec=0;

	sock=socket(AF_INET,SOCK_DGRAM,0);
	if (sock<0) {
		printf("HandleIPFound:sock init error\n");
		return 1;
	}

	broadcast_addr.sin_family=AF_INET;
	broadcast_addr.sin_port=htons(MCAST_PORT);
	broadcast_addr.sin_addr.s_addr = htonl(INADDR_BROADCAST);

	ret = setsockopt(sock,SOL_SOCKET,SO_BROADCAST,&so_broadcast,sizeof(so_broadcast));

	char recvbuf[1024] = {0};
	int times=10;
	int i=0;
	for (i=0; i<times; i++) {
		timeout.tv_sec=2;
		timeout.tv_usec=0;
		printf("==> broadcast IP :%s Port:%d\n",inet_ntoa(broadcast_addr.sin_addr), ntohs(broadcast_addr.sin_port));
		ret = sendto(sock,&sendmsg,sizeof(sendmsg),0,(struct sockaddr*)&broadcast_addr,sizeof(broadcast_addr));
		if (ret==-1) {
			continue;
		}

		FD_ZERO(&readfd);
		FD_SET(sock,&readfd);

		ret = select(sock+1,&readfd,NULL,NULL,&timeout);
		switch (ret) {
			case -1:
				break;
			case 0:
				//printf("timeout\n");
				break;
			default:
				if(FD_ISSET(sock,&readfd)) {
					memset(recvbuf, 0, sizeof(recvbuf));
					memset((char*)&recvmsg, 0, sizeof(recvmsg));
					count=recvfrom(sock,recvbuf,sizeof(recvbuf),0,(struct sockaddr*)&from_addr,&from_len);
					if (count == sizeof(recvmsg))
						memcpy(&recvmsg, recvbuf, sizeof(recvmsg));
					if (strstr(recvmsg.id,BCAST_ACK)) {
						printf("<== found server IP :%s\n",inet_ntoa(from_addr.sin_addr));
						print_msg(recvmsg);
						//printf("Server Port:%d\n",htons(from_addr.sin_port));
					}
					return 1;  
				}
				break;
		}
	}

	return 0;
}

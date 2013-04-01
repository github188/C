#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <stdlib.h>
#include <arpa/inet.h>

#include "commdef.h"
#include "common.h"

int main(int argc,char*argv[]) {
	int ret=-1;
	int sock;
	struct sockaddr_in server_addr;
	struct sockaddr_in from_addr;
	int from_len=sizeof(struct sockaddr_in);
	int count=-1;
	fd_set readfd;

	struct timeval timeout;
	timeout.tv_sec=2;
	timeout.tv_usec=0;

	sock=socket(AF_INET,SOCK_DGRAM,0);
	if (sock<0) {
		perror("sock error");
		return 1;
	}

	memset((void*)&server_addr,0,sizeof(struct sockaddr_in));
	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr=htons(INADDR_ANY);
	server_addr.sin_port=htons(MCAST_PORT);
	ret=bind(sock,(struct sockaddr*)&server_addr,sizeof(server_addr));
	if (ret<0) {
		perror("bind error");
		return 1;
	}

	struct bcast_msg recvmsg;
	struct bcast_msg sendmsg;

	strncpy(sendmsg.id, BCAST_ACK, sizeof(sendmsg.id));
	sendmsg.type = 2;
	sendmsg.function = 1;
	memset((char*)&(sendmsg.devinfo), 0, sizeof(sendmsg.devinfo));
	sendmsg.devinfo.dev = '3';
	strncpy(sendmsg.devinfo.name, "testdev001", sizeof(sendmsg.devinfo.name));
	strncpy(sendmsg.devinfo.ifname, "eth0", sizeof(sendmsg.devinfo.ifname));
	strncpy(sendmsg.devinfo.ip, "172.16.50.126", sizeof(sendmsg.devinfo.ip));
	strncpy(sendmsg.devinfo.mac, "14:CF:92:23:B5:BF", sizeof(sendmsg.devinfo.mac));

	char recvbuf[1024] = {0};

	while (1) {
		timeout.tv_sec=2;
		timeout.tv_usec=0;
		FD_ZERO(&readfd);
		FD_SET(sock,&readfd);

		ret=select(sock+1,&readfd,NULL,NULL,&timeout);
		switch (ret) {
			case -1:
				break;
			case 0:
				//printf("timeout\n");
				break;
			default:
				if (FD_ISSET(sock,&readfd)) {
					memset(recvbuf, 0, sizeof(recvbuf));
					memset((char*)&recvmsg, 0, sizeof(recvmsg));
					count=recvfrom(sock,recvbuf,1024,0,(struct sockaddr*)&from_addr,&from_len);
					if (count == sizeof(recvmsg))
					{
						memcpy(&recvmsg, recvbuf, sizeof(recvmsg));
						if (strstr(recvmsg.id,BCAST_ASK)) {
							//char strIP[INET_ADDRSTRLEN] = {0};
							//inet_ntop(AF_INET, &from_addr.sin_addr, strIP, sizeof(strIP));
							//printf("client ip %s\n",strIP);
							printf("Client IP %s, ",inet_ntoa(from_addr.sin_addr));
							printf("Port:%d\n",ntohs(from_addr.sin_port));
							//print_msg(sendmsg);
							count=sendto(sock,&sendmsg,sizeof(sendmsg),0,(struct sockaddr*)&from_addr,from_len);
						}
					}
				}
				break;
		}
	}
	return 0;
}

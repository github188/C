// Get mac address with NetBIOS protocol
// compile with gcc on linux
// Create by Dennis
// 2013-04-10
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

#define NETBIOS_PORT 137

unsigned char bs[50]={ 
	0x0,0x00,0x0,0x10,0x0,0x1,0x0,0x0,0x0,0x0,0x0,0x0,0x20,0x43,0x4b,0x41,0x41, 
	0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41, 
	0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x0,0x0, 
	0x21,0x0,0x1
};

// 通过NbtStat获取计算机名字信息的结构体  
struct names  
{  
	unsigned char nb_name[16];  // 表示接收到的名字  
	unsigned short name_flags;  // 标识名字的含义  
}; 

void print_buf(unsigned char* buf, int len)
{
	int i = 0;
	for (i=0; i<len; i++)
	{
		if (i%8==0) printf("\n%04d: ", i);
		printf("0x%02x ", buf[i]);
	}
	printf("\n");
}

void parse_netbios(char* buf, int len)
{
	//print_buf(buf, len);
	char* respuesta = buf;

	// 定义名字数组  
	struct names Names[20*sizeof(struct names)]; 

	int count = 0;

	// 将count定位到名字表中名字的数量。在NetBIOS回应包中，前面56位是网络适配器的状态信息  
	memcpy(&count, respuesta+56, 1);  
	if(count > 20){      // 最多有20个名字，超出则错误  
		return;  
	}  

	// 将名字表内在复制到Names数组中  
	memcpy(Names,(respuesta+57), count*sizeof(struct names));  

	// 将空格字符替换成空  
	unsigned int i,j;
	for(i = 0; i < count;i++) {  
		for(j = 0;j < 15;j++){  
			if(Names[i].nb_name[j] == 0x20)  
				Names[i].nb_name[j]=0;  
		}  
	}

	for(i=0;i<count;i++){  
		// 如果最后一位是0x00，则表示当前名字表项为保存计算机名或者工作组  
		if(Names[i].nb_name[15] == 0x00){  
			char buffers[17] = {0};  
			memcpy(buffers, Names[i].nb_name, 16);  
			// 使用name_flags字段来区分当前名字是计算机名还是工作组  
			if((Names[i].name_flags & 128) == 0) {  
				printf(" name: %s\n", buffers);
			}  
			else{  
				printf("group: %s\n", buffers);
			}  
		}  
	}  

	unsigned char mac[6];
	// 名字表后面是MAC地址  
	memcpy(mac,(respuesta+57+count*sizeof(struct names)),6);  
	printf("  mac: %02x-%02x-%02x-%02x-%02x-%02x\n", 
		mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);
}

int main(int argc,char*argv[]) {
	int ret=-1;
	int sock=-1;
	//int so_broadcast=1;
	struct sockaddr_in server_addr;
	struct sockaddr_in from_addr;
	int from_len=sizeof(from_addr);
	int count=-1;
	fd_set readfd;

	struct timeval timeout;
	timeout.tv_sec=2;
	timeout.tv_usec=0;

	sock=socket(AF_INET,SOCK_DGRAM,0);
	if (sock<0) {
		printf("HandleIPFound:sock init error\n");
		return 1;
	}

	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(NETBIOS_PORT);
	//server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (argc > 1)
		server_addr.sin_addr.s_addr = inet_addr(argv[1]);
	else
		server_addr.sin_addr.s_addr = inet_addr("192.168.50.39");

	//ret = setsockopt(sock,SOL_SOCKET,SO_BROADCAST,&so_broadcast,sizeof(so_broadcast));

	char recvbuf[1024] = {0};
	int times=10;
	int i=0;
	for (i=0; i<times; i++) {
		timeout.tv_sec=2;
		timeout.tv_usec=0;
		//printf("==> IP :%s Port:%d\n",inet_ntoa(server_addr.sin_addr), ntohs(server_addr.sin_port));
		ret = sendto(sock,&bs,sizeof(bs),0,(struct sockaddr*)&server_addr,sizeof(server_addr));
		if (ret==-1) {
			printf("Failed to do sendto\n");
			continue;
		}

		FD_ZERO(&readfd);
		FD_SET(sock,&readfd);

		ret = select(sock+1,&readfd,NULL,NULL,&timeout);
		switch (ret) {
			case -1:
				break;
			case 0:
				printf("timeout\n");
				break;
			default:
				if(FD_ISSET(sock,&readfd)) {
					memset(recvbuf, 0, sizeof(recvbuf));
					count=recvfrom(sock,recvbuf,sizeof(recvbuf),0,(struct sockaddr*)&from_addr,&from_len);
					printf("   ip: %s\n", inet_ntoa(from_addr.sin_addr));
					parse_netbios(recvbuf, count);
					return 1;  
				}
				break;
		}
	}

	return 0;
}

/**
 * platform_def.h
 *
 */

#ifndef _PLATFORM_DEF_H_
#define _PLATFORM_DEF_H_

#include <stdio.h>

#if defined WIN32
	#warning "*********** Do Win32 platform compile *************"
	#define _CRT_SECURE_NO_DEPRECATE

	// define in windows.h, for reduce header include, speed up build process
	#ifndef WIN32_LEAN_AND_MEAN
	#define WIN32_LEAN_AND_MEAN		
	#endif

	#include <windows.h>
	#include <winsock2.h>
	#pragma comment(lib, "ws2_32.lib")
	#include <process.h>
	#include <malloc.h>
	#include <assert.h>
	#include <time.h>

#elif defined LINUX
	#warning "*********** Do Linux platform compile *************"
	/* TCP/IP */
	#include <sys/socket.h>
	#include <sys/select.h> 
	#include <sys/time.h>
	#include <netinet/in.h>
	#include <arpa/inet.h> 

	#include <sys/ioctl.h>
	#include <net/if.h>
	
	/* Thread */
	#include <sched.h>
	#include <pthread.h>
	/* Malloc,Free */
	#include <stdlib.h>
	#include <string.h>
	#include <unistd.h>
	#include <fcntl.h>
	#include <errno.h>
	#include <assert.h>
	/* sign */
	#include <stdio.h>
	#include <time.h>
	#include <signal.h>

#elif defined VXWORKS
	#warning "*********** Do VXWORKS platform compile *************"
	#include <time.h>
	/* TCP/IP */
	#include <sockLib.h>
	#include <selectLib.h> 

	#include <netinet/in.h>
	#include <netinet/tcp.h>
	#include <arpa/inet.h> 
	/* Thread */
	#include <sched.h>
	#include <taskLib.h>
	#include <pthread.h>
	/* Malloc,Free */
	#include <stdlib.h>
	#include <string.h>
	#include <unistd.h>
	#include <ioLib.h>
	#include <ioctl.h>
	#include <errno.h>
	#include <assert.h>

#endif

#if defined WIN32

	typedef int BOOL;
	typedef signed char INT8, *PINT8;
	typedef unsigned char UINT8, *PUINT8;

	typedef signed short INT16, *PINT16;
	typedef unsigned short UINT16, *PUINT16;

	typedef signed int INT32, *PINT32;
	typedef unsigned int UINT32, *PUINT32;

#elif defined LINUX

	typedef int BOOL;
	typedef signed char INT8, *PINT8;
	typedef signed char CHAR, *PCHAR;
	typedef unsigned char UINT8, *PUINT8;
	typedef unsigned char UCHAR, *PUCHAR;

	typedef signed short INT16, *PINT16;
	typedef signed short SHORT, *PSHORT;
	typedef unsigned short UINT16, *PUINT16;
	typedef unsigned short USHORT, *PUSHORT;

	typedef signed int INT32, *PINT32;
	typedef signed int LONG, *PLONG;
	typedef unsigned int UINT32, *PUINT32;
	typedef unsigned int ULONG, *PULONG;

#elif defined VXWORKS

	typedef signed char *PINT8;
	typedef signed char *PCHAR;
	typedef unsigned char *PUINT8;
	typedef unsigned char *PUCHAR;

	typedef signed short *PINT16;
	typedef signed short *PSHORT;
	typedef unsigned short *PUINT16;
	typedef unsigned short *PUSHORT;

	typedef signed int *PINT32;
	typedef signed int *PLONG;
	typedef unsigned int *PUINT32;
	typedef unsigned int *PULONG;

#endif

#ifndef NULL
#define NULL 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#define ENTER_FUNC() printf("+ %s\n", __func__);
#define EXIT_FUNC()  printf("- %s\n", __func__);

#endif // _PLATFORM_DEF_H_


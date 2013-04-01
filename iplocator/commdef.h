// commdef.h

#ifndef _COMMDEF_H_
#define _COMMDEF_H_

// verify both of communicator, length 29+1
#define BCAST_ASK "BCAST-ASK-E677-B97A-B1D8-A81F"
#define BCAST_ACK "BCAST-ACK-9966-32C4-6A2D-527D"

// Broadcast port
#define MCAST_PORT 9999

// Device information, length 69
struct dev_info {
	char dev;			// device id
	char name[18];		// device name
	char mac[18];		// mac address
	char ip[25];		// ip address
	char ifname[10];	// interface name
};

// Broadcast message structure, length 32+69
struct bcast_msg {
	char id[32];		// ID, length is equal to BCAST_ASK or BCAST_ACK's size
	char type;			// 1|2: client|server message
	char function;		// if id is 1, avariable values:
						// 1: get info
						// 2: set info
						// if id is 2, it is ignored 
	struct dev_info devinfo;
};

#endif

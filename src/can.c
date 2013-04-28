#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <syslog.h>

#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>

#include <linux/can.h>
#include <linux/can/raw.h>

#include "can.h"

int can_init(const char* ifname) {
	int cansock;

	struct sockaddr_can addr;
	struct ifreq ifr;

	syslog(LOG_DEBUG,"initializing cansocket...");

	if ((cansock = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
        syslog(LOG_CRIT, "failed to initialize socket!");
		return -1;
	}

	strcpy(ifr.ifr_name, ifname);
	ioctl(cansock, SIOCGIFINDEX, &ifr);
	
	addr.can_family = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;

    syslog(LOG_DEBUG, "opened interface %s at index %d", ifname, ifr.ifr_ifindex);
	
	if (bind(cansock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		syslog(LOG_CRIT, "[ERROR] binding socket");
		return -1;
	}

    syslog(LOG_DEBUG, "bound can socket");
    return cansock;
}

// blocking read of a can message
int can_read(int cansock, struct can_frame *frame)
{
    struct can_frame tmp_frame;

    // wait for a valid read
    while(read(cansock, &tmp_frame, sizeof(struct can_frame)) < 0);

    // pass back the frame
    memcpy(frame, &tmp_frame, sizeof(struct can_frame));

    return 0;
}

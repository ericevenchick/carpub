#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <syslog.h>
#include <pthread.h>
#include <signal.h>

#include <sys/socket.h>
#include <linux/can.h>

#include "canstore.h"
#include "carpub.h"

int main (void) {
    carpub_t carpub;
    canstore_t canstore;

    // initialize logging
    openlog("carserver", LOG_PID|LOG_CONS, LOG_USER);
    syslog(LOG_INFO, "starting carserver...");

    // initialize canstore
    canstore = canstore_init("can0");
    // initialize carpub, attach to canstore
    carpub = carpub_init("tcp://*:5555", canstore);

    // launch canstore
    canstore_start(canstore);
    // launch carpub
    carpub_start(carpub);

    for (;;);

    return 0;
}

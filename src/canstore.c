#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <syslog.h>
#include <string.h>

#include <sys/socket.h>
#include <linux/can.h>

#include "can.h"
#include "canstore.h"

struct canstore_priv_data * canstore_init(const char *iface)
{
    canstore_t canstore_data = malloc(sizeof(struct canstore_priv_data));
    memset(&(canstore_data->values), 0, sizeof(canstore_data->values));

    // get a socket to the CAN bus
    canstore_data->cansock = can_init(iface);

    // return a pointer to the internal data
    return canstore_data;
}

int canstore_start(canstore_t canstore_data) 
{
    pthread_t canstore_thread;
    syslog(LOG_DEBUG, "creating canstore task");

    // start canstore_task in its own thread
    pthread_create(&(canstore_thread), NULL,
                   canstore_task, (void *)canstore_data);
    return 0;
}

void *canstore_task(void *void_canstore_data)
{
    canstore_t canstore_data = (canstore_t)void_canstore_data;
    struct can_frame recv_frame;

    syslog(LOG_DEBUG, "starting canstore task");
    for (;;) {
        #ifdef FAKE_CAN
        // when fake can is enabled, just populate ID 0x400 with 4 random bytes
        recv_frame.can_id = 0x410;
        recv_frame.can_dlc = 4;
        recv_frame.data[0] = rand();
        recv_frame.data[1] = rand();
        recv_frame.data[2] = rand();
        recv_frame.data[3] = 51;
        sleep(1);
        #else
        // blocking read, wait for can data
        can_read(canstore_data->cansock, &recv_frame);
        #endif

        // parse and store data
        canstore_parse_frame(canstore_data, recv_frame);
    }
}

void canstore_parse_frame(canstore_t canstore_data, struct can_frame frame)
{
    double real;
    switch (frame.can_id) {
        case CANSTORE_CANID_BCM_STATUS:
            // bcm_soc, byte 3, scale 0.5
            real = frame.data[3] * 0.5;
            canstore_set(canstore_data, CANSTORE_VALUE_HV_SOC, real);
            break;
        case CANSTORE_CANID_BCM_DATA_1:
            // bcm_lvbat
            canstore_set(canstore_data, CANSTORE_VALUE_LV_VOLT, frame.data[7]);
            break;
    }
}

int canstore_set(canstore_t canstore_data, int id, double value)
{
    if (id < NUM_STORE_VALUES) {
        canstore_data->values[id] = value;
    } else {
        return -1;
    }
}

double canstore_get(canstore_t canstore_data, int id)
{
    if (id < NUM_STORE_VALUES) {
        return canstore_data->values[id];
    } else {
        return -1;
    }
}

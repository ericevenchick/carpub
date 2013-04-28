#include <sys/socket.h>
#include <linux/can.h>

#include "canstore.h"
#include "canstore_parser.h"

void canstore_parse_frame(canstore_t canstore_data, struct can_frame frame)
{
    double real;

    switch (frame.can_id) {
        case CANSTORE_CANID_BCM_STATUS:
            // bcm_soc, byte 3, scale 0.5, unit %
            real = frame.data[3] * 0.5;
            canstore_set(canstore_data, CANSTORE_VALUE_BCM_HV_SOC, real);

            // bcm_gfd, bits 11-16, factor 0.25, unit kOhm
            real = (frame.data[2] + ((frame.data[1] & 0xF) << 4)) * 0.25;
            canstore_set(canstore_data, CANSTORE_VALUE_BCM_GFD, real);
            break;

        case CANSTORE_CANID_BCM_DATA_1:
            // bcm_lvbat, byte 7, scale 0.1, unit volts
            real = frame.data[7] * 0.1;
            canstore_set(canstore_data, CANSTORE_VALUE_BCM_LV_VOLT, real);
            break;
    }
}

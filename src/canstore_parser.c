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
            canstore_set(canstore_data, CANSTORE_VALUE_BCM_SOC, real);

            // bcm_gfd, bits 8-23, factor 0.25, unit kOhm
            real = (frame.data[2] + ((frame.data[1] & 0xF) << 4)) * 0.25;
            canstore_set(canstore_data, CANSTORE_VALUE_BCM_GFD, real);

            // bcm_ibat, bits 32-47, factor 0.025, offset -1000
            real = ((frame.data[4] << 8) + frame.data[5]) * 0.025 - 1000;
            canstore_set(canstore_data, CANSTORE_VALUE_BCM_IBAT, real);
            break;

        case CANSTORE_CANID_BCM_DATA_1:
            // bcm_lvbat, byte 7, scale 0.1, unit volts
            real = frame.data[7] * 0.1;
            canstore_set(canstore_data, CANSTORE_VALUE_BCM_LVBATT, real);
            break;
    }
}

#ifndef CANSTORE_PARSER_H_INCLUDED
#define CANSTORE_PARSER_H_INCLUDED

// keys
#define CANSTORE_VALUE_BCM_HV_SOC 0
#define CANSTORE_VALUE_BCM_GFD 1
#define CANSTORE_VALUE_BCM_LV_VOLT 2

// CAN IDs
#define CANSTORE_CANID_BCM_STATUS 0x410
#define CANSTORE_CANID_BCM_DATA_1 0x430

void canstore_parse_frame(canstore_t canstore_data, struct can_frame frame);

#endif

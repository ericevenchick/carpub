#ifndef CANSTORE_H_INCLUDED
#define CANSTORE_H_INCLUDED

#define FAKE_CAN 1
#define NUM_STORE_VALUES 10

// keys
#define CANSTORE_VALUE_HV_SOC 0
#define CANSTORE_VALUE_LV_VOLT 1

// CAN IDs
#define CANSTORE_CANID_BCM_STATUS 0x410
#define CANSTORE_CANID_BCM_DATA_1 0x430

struct canstore_priv_data {
    int cansock;
    double values[NUM_STORE_VALUES];
};
typedef struct canstore_priv_data *canstore_t;

struct canstore_priv_data * canstore_init(const char *iface);
int canstore_start(canstore_t canstore_data);
void *canstore_task(void *void_canstore_data);
void canstore_parse_frame(canstore_t canstore_data, struct can_frame frame);
int canstore_set(canstore_t canstore_data, int id, double value);
double canstore_get(canstore_t canstore_data, int id);

#endif

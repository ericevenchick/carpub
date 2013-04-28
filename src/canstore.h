#ifndef CANSTORE_H_INCLUDED
#define CANSTORE_H_INCLUDED

#define FAKE_CAN 1

#define NUM_STORE_VALUES 10

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

#include "canstore_parser.h"

#endif

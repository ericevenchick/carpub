#ifndef CARPUB_H_INCLUDED
#define CARPUB_H_INCLUDED

struct carpub_priv_data {
    void *sock;
    canstore_t canstore;
};
typedef struct carpub_priv_data *carpub_t;

struct carpub_priv_data * carpub_init(const char *connect_str, canstore_t canstore);
void *carpub_task(void *id);
int carpub_start(carpub_t carpub_data);
void carpub_log_error(void);
int carpub_publish(carpub_t carpub_data, char *resp_buffer);

#endif

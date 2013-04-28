#ifndef CARPUB_H_INCLUDED
#define CARPUB_H_INCLUDED

void *carpub_init(const char *connect_str);
void carpub_log_error(void);
int carpub_publish(void *netsock, char *resp_buffer);

#endif

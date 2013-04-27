#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED

void *server_init(void);
int server_get_req(void *netsock, char *req_buffer);
void server_log_error(void);
int server_send_resp(void *netsock, char *resp_buffer);

#endif

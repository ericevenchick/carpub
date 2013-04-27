#include <zmq.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <syslog.h>

#include "server.h"

void* server_init(void) {
    syslog(LOG_DEBUG, "initializing network");
    void *context = zmq_ctx_new ();
    void *netsock = zmq_socket(context, ZMQ_REP);
    int rc = zmq_bind (netsock, "tcp://*:5555");
    assert (rc == 0);

    return netsock;
}

void server_log_error(void) {
    int e = zmq_errno();
    const char *errstr;
    errstr = zmq_strerror(e);
    syslog(LOG_DEBUG, "network error: %s", errstr);
}

// blocking call to read a request from a client
int server_get_req(void *netsock, char *req_buffer) {
    int status;
    status = zmq_recv(netsock, req_buffer, 10, 0);
    if (status < 0) {
        server_log_error();
        return -1;
    }
    return 0;
}

// send a response to the client
int server_send_resp(void *netsock, char *resp_buffer) {
    int status;
    status = zmq_send(netsock, resp_buffer, 10, 0);
    if (status < 0) {
        server_log_error();
        return -1;
    }
    return 0;
}

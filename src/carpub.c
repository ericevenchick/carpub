#include <zmq.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <syslog.h>

#include "carpub.h"

void* carpub_init(const char *connect_str) {
    syslog(LOG_DEBUG, "initializing network");
    void *context = zmq_ctx_new ();
    void *netsock = zmq_socket(context, ZMQ_PUB);
    int rc = zmq_bind (netsock, connect_str);
    assert (rc == 0);

    return netsock;
}

void carpub_log_error(void) {
    int e = zmq_errno();
    const char *errstr;
    errstr = zmq_strerror(e);
    syslog(LOG_DEBUG, "carpub error: %s", errstr);
}

// send a response to the client
int carpub_publish(void *netsock, char *buffer) {
    int status;
    status = zmq_send(netsock, buffer, strlen(buffer), 0);
    if (status < 0) {
        carpub_log_error();
        return -1;
    }
    return 0;
}

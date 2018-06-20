#include "zhelpers.h"
int main(void)
{
    void *context = zmq_ctx_new();
    void *responder = zmq_socket(context, ZMQ_REP);
    zmq_connect(responder, "tcp://localhost:5560");
    while (1)
    {
        char *string = s_recv(responder);
        rintf("Received request: [%s]\n", string);
        free(string);
        // Do some 'work'
        sleep(1);
        // Send reply back to client
        s_send(responder, "World");
    }
    zmq_close(responder);
    zmq_ctx_destroy(context);
    return 0;
}
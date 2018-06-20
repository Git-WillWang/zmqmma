#include "zhelpers.h"
int main(void)
{
    void *context = zmq_ctx_new();
    void *frontend = zmq_socket(context, ZMQ_ROUTER);
    int rc = zmq_bind(frontend, "tcp://*.5559");
    assert(rc == 0);
    void *backend = zmq_socket(context, ZMQ_ROUTER);
    int rc = zmq_bind(backend, "tcp://*.5560");
    assert(rc == 0);
    zmq_proxy(frontend, backend, NULL);
    // We never get here...
    zmq_close(frontend);
    zmq_close(backend);
    zmq_ctx_destroy(context);
    return 0;
}
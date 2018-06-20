/*
    
*/
#include "zhelpers.h"
int main()
{
    void *context = zmq_ctx_new();
    void *receiver = zmq_socket(context, ZMQ_PULL);
    zmq_connect(receiver, "tcp://localhost:5557");

    void *subscriber = zmq_socket(context, ZMQ_SUB);
    zmq_connect(subscriber, "tcp://localhost:5556");
    zmq_setsockopt(subscriber, ZMQ_SUBSCRIBE, "10001", 6);

    while (1)
    {
        int rc;
        for (rc = 0; !rc;)
        {
            zmq_msg_t task;
            zmq_msg_init(&task);
            if ((rc = zmq_msg_recv(&task, receiver, ZMQ_DONTWAIT)) != -1)
            {
            }
            zmq_msg_close(&task);
        }
        for (rc = 0; !rc;)
        {
            zmq_msg_t update;
            zmq_msg_init(&update);
            if ((rc = zmq_msg_recv(&update, subscriber, ZMQ_DONTWAIT)) != -1)
            {
            }
            zmq_msg_close(&update);
        }
    }
    zmq_close(receiver);
    zmq_close(subscriber);
    return 0;

    
}

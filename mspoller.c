#include"zhelpers.h"
int main(){
    void *context= zmq_ctx_new();
    void *receiver = zmq_socket(context,ZMQ_PULL);
    zmq_connect(receiver,"tcp://localhost:5557");
    void *subscriber = zmq_socket(context,ZMQ_SUB);
    zmq_connect(subscriber,"tcp://localhost:5556");
    zmq_setsockopt(subscriber,ZMQ_SUBSCRIBE,"10001",6);
    zmq_pollitem_t items[] ={{receiver,0,ZMQ_POLLIN,0},{subscriber,0,ZMQ_POLLIN,0}};
    while(1){
        zmq_msg_t message;
        zmq_poll(items,2,-1);
        if(items[0].revents & ZMQ_POLLIN){
            zmq_msg_init(&message);
            zmq_msg_recv(&message,receiver,0);
            zmq_msg_close(&message);
        }
        if(items[1].revents&ZMQ_POLLIN){
            zmq_msg_init(&message);
            zmq_msg_recv(&message,subscriber,0);
            zmq_msg_close(&message);
        }
    }
    zmq_close(receiver);
    zmq_close(subscriber);
    zmq_ctx_destroy(context);
    return 0;
    
}
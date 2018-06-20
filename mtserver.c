#include"zhelpers.h"
#include<pthread.h>
static void* worker_routine(void *context){
    void *receiver = zmq_socket(context,ZMQ_REP);
    zmq_connect(receiver,"inproc://workers");
    while(1){
        char *string = s_recv(receiver);
        printf("Received request: [%s]\n",string);
        free(string);
        sleep(1);
        s_send(receiver,"World");
    }
    zmq_close(receiver);
    return NULL;
}
int main(void){
    void *context = zmq_ctx_new();
    void *clients = zmq_socket(context,ZMQ_ROUTER);
    zmq_bind(clients,"tcp://*:5555");
    void *workers = zmq_socket(context,ZMQ_DEALER);
    zmq_bind(workers,"inproc://workers");
    int thread_nbr;
    for(thread_nbr = 0;thread_nbr<5;thread_nbr++){
        pthread_t worker;
        pthread_create(&worker,NULL,worker_routine,context);
    }
    zmq_proxy(clients,workers,NULL);
    zmq_close(clients);
    zmq_close(workers);
    zmq_ctx_destroy(context);
    return 0;
}
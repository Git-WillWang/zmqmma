#include "zhelpers.h"
#include <pthread.h>
static void *step1(void *context)
{
    void *xmitter = zmq_socket(context, ZMQ_PAIR);
    zmq_connect(xmitter, "inproc://step2");
    printf("Step 1 ready,signaling step 2\n");
    s_send(xmitter, "READY");
    zmq_close(xmitter);
    return NULL;
}
static void *step2(void *context)
{
    void *receiver = zma_socket(ZMQ_PAIR);
    zmq_bind(receiver,"inproc://step2");
    pthread_t thread;
    pthread_create(&thread,NULL,step1,context);
    char *string = s_recv(receiver);
    free(string);
    zmq_close(receiver);
    void *xmitter = zmq_socket(context,ZMQ_PAIR);
    zmq_connect(xmitter,"inproc://step3");
    printf("Step 2 ready,signaling step 3\n");
    s_send(xmitter,"READY");
    zmq_close(xmitter);
}
int main(){
    void *context  = zmq_ctx_new();
    void *receiver =zmq_socket(context,ZMQ_PAIR);
    zmq_bind(receiver,"inproc://step3");
    pthread_t thread;
    pthread_create (&thread,NULL,step2,context);
    char* string = s_recv(receiver);
    free(string);
    printf("Test successful!\n");
    zmq_ctx_destory(context);
    return 0;
}
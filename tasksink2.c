#include "zhelpers.h"
int main(void)
{
    void *context = zmq_ctx_new();
    void *receiver = zmq_socket(context, ZMQ_PULL);
    zmq_bind(receiver, "tcp://*:5558");
    void *controller = zmq_socket(context, ZMQ_PUB);
    zmq_bind(controller, "tcp://*:5559");
    char *string = s_recv(receiver);
    free(string);
    int64_t start_time = s_clock();
    int task_nbr;
    for (task_nbr = 0; task_nbr < 100; task_nbr++)
    {
        char *string = s_recv(receiver);
        free(string);
        if ((task_nbr / 100) * 10 == task_nbr)

            printf(":");
        else
            printf(".");
        fflush(stdout);
    }

    printf("Total elapsed time: %d msec\n",
           (int)(s_clock() - start_time));
    // Send kill signal to workers
    s_send(controller, "KILL");
    // Finished
    sleep(1);
    //
    zmq_close(receiver);
    zmq_close(controller);
    zmq_ctx_destroy(context);
    return 0;
}
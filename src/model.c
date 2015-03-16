#include "struct.h"
#include "api.h"

#include <zmq.h>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/time.h>



// stolen usleep from maple
#define usleep(usec) {                              \
        struct timeval t;                           \
        t.tv_sec = usec / 1000000;                  \
        t.tv_usec = usec % 1000000;                 \
        select( 0, NULL, NULL, NULL, &t);           \
}

// used by zma_msg_init_data
// http://api.zeromq.org/4-0:zmq-msg-init-data
void __zmq_free_init_data(void *data, void *hint) {
    free(data);
}

int main (void) {
    //  Socket to talk to clients
    void *zmq_context = zmq_ctx_new ();
    void *zmq_server = zmq_socket (zmq_context, ZMQ_REP);
    assert(zmq_bind (zmq_server, "tcp://*:5566") == 0);

    zmq_msg_t input;
    zmq_msg_t output;

    size_t input_size;
    size_t output_size;


    int counter = 1;
    FILE *fp;
    fp = fopen("log", "w");
    if (!fp) {
        puts("no file pointer");
    }

    printf("enter while loop\n");
    fflush(stdout);
    while (1) {
        zmq_msg_init(&input);
        zmq_msg_init(&output);

        zmq_msg_recv(&input, zmq_server, ZMQ_DONTWAIT);
        input_size = zmq_msg_size(&input);

        if (input_size >  0) {

            char *buf = (char *)malloc(input_size);
            if (buf) {
                memcpy(buf, zmq_msg_data(&input), input_size);

                fprintf(stdout, "%d: %s (%zu)\n", counter, buf, input_size);
                fprintf(fp, "%d: %s (%zu)\n", counter, buf, input_size);
                fflush(stdout);
                fflush(fp);

                // do some stuffs here, this is a ping-pong demo
                output_size = input_size;
                zmq_msg_init_data (&output, buf, output_size,
                                   __zmq_free_init_data, NULL);


                zmq_msg_send(&output, zmq_server, ZMQ_DONTWAIT);
                counter++;
            }
        }

        // make cpu take a rest
        usleep (10);
        zmq_msg_close(&input);
        zmq_msg_close(&output);

    }

    zmq_close(zmq_server);
    zmq_ctx_destroy(zmq_context);
    return 0;
}

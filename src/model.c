#include "struct.h"
#include "api.h"

#include <zmq.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <sys/time.h>



// stolen usleep from maple
#define usleep(usec) {                              \
        struct timeval t;                           \
        t.tv_sec = usec / 1000000;                  \
        t.tv_usec = usec % 1000000;                 \
        select( 0, NULL, NULL, NULL, &t);           \
}

int main (void) {
    //  Socket to talk to clients
    void *zmq_context = zmq_ctx_new ();
    void *zmq_server = zmq_socket (zmq_context, ZMQ_REP);
    assert(zmq_bind (zmq_server, "tcp://*:5555") == 0);

    char input [2048];
    char output [2048];

    int counter = 1;
    FILE *fp;
    fp = fopen("log", "w");
    if (!fp) {
        puts("no file pointer");
    }

    while (1) {
        memset(input, 0, 2048);
        memset(output, 0, 2048);
        zmq_recv(zmq_server, input, 2048, ZMQ_DONTWAIT);

        if (input[0]) {
            // do some stuffs here
            sprintf(output, "%s: %d", input, counter);
            fprintf(fp, "%s %d\n", input, counter);
            fflush(fp);
            counter++;
        }
        // make cpu take a rest
        usleep (10);

        zmq_send(zmq_server, output, 2048, ZMQ_DONTWAIT);
    }

    zmq_close(zmq_server);
    zmq_ctx_destroy(zmq_context);
    return 0;
}

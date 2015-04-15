#include "api.h"
#include "json.h"
#include "struct.h"

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

// used by zmq_msg_init_data
// http://api.zeromq.org/4-0:zmq-msg-init-data
void __zmq_free_init_data (void *data, void *hint) {
    free(data);
    data = NULL;
    hint = NULL;
}

struct __api_route {
    char *name;
    char* (*func)(const char*);
};

#define DEF_API_ROUTE(api_name) { str(api_name), api_name }

const struct __api_route api_route[] = {
    DEF_API_ROUTE(board_new),
    DEF_API_ROUTE(board_get),
    DEF_API_ROUTE(board_list),
    DEF_API_ROUTE(board_length),
    DEF_API_ROUTE(board_post_list),
    DEF_API_ROUTE(board_post_length),
    DEF_API_ROUTE(board_inner_post_list),
    DEF_API_ROUTE(board_inner_post_length),
    DEF_API_ROUTE(board_post_path),
    DEF_API_ROUTE(user_new),
    DEF_API_ROUTE(user_get),
    DEF_API_ROUTE(user_length),
    DEF_API_ROUTE(user_fav_list),
    DEF_API_ROUTE(user_fav_list_length),
    DEF_API_ROUTE(class_items_list),
};

#undef DEF_API_ROUTE

// dispatch a message to a coresponding API call
// returning a message to be sent to ZMQ
void dispatch (const char *buf_i, const size_t size_i,
                     char **buf_o, size_t *size_o) {
    unsigned int i;
    /* Init output parameters */
    *buf_o = NULL;
    *size_o = 0;

    /* Check input */
    if (!buf_i || !size_i) return;

    char *API_name = get_API_name(buf_i);
    if (!API_name) {
        fprintf(stderr, "Parameter required: `api`.\n");
        return;
    }

    for (i = 0; i < countof(api_route); ++i) {
        if (!strcmp(API_name, api_route[i].name)) {
            *buf_o = (*api_route[i].func)(buf_i);
            break;
        }
    }
    if (i == countof(api_route)) {
        fprintf(stderr, "API not found: `%s`.\n", API_name);
    }

    *size_o = *buf_o ? strlen(*buf_o) : 0;

    free(API_name);
    API_name = NULL;
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

                char *buf_o = NULL;

                // dispatch API calls, this will return JSON strings of results
                dispatch(buf, input_size, &buf_o, &output_size);

                free(buf);
                buf = NULL;

                zmq_msg_init_data (&output, buf_o, output_size,
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

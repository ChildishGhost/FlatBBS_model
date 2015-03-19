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
}


// dispatch a message to a coresponding API call
// returning a message to be sent to ZMQ
void dispatch (const char *buf_i, const size_t size_i,
                     char **buf_o, size_t *size_o) {

    if (!buf_i || !size_i) {
        *buf_o = NULL;
        *size_o = 0;
        return;
    }

    unsigned bid;
    unsigned uid;
    unsigned length;
    unsigned offset;

    char *API_name = get_API_name(buf_i);
    if (API_name) {

        if (!strcmp(API_name, "board_new")) {
            char *name = get_name(buf_i);
            utf8 *category = get_category(buf_i);
            utf8 *title = get_title(buf_i);
            unsigned *masters = get_masters(buf_i);
            const unsigned masters_count = get_masters_count(buf_i);
            const enum BOARD_PERM perm = get_perm(buf_i);
            const unsigned attr = get_attr(buf_i);

            *buf_o = board_new (name, category, title,
                                masters, masters_count,
                                perm, attr);
            free(name);
            free(category);
            free(title);
            free(masters);
        }
        else if (!strcmp(API_name, "board_list")) {
            offset = get_offset(buf_i);
            length = get_length(buf_i);
            *buf_o = board_list(offset, length);
        }
        else if (!strcmp(API_name, "board_length")) {
            length = get_length(buf_i);
            *buf_o = board_length();
        }
        else if (!strcmp(API_name, "board_post_list")) {
            bid = get_bid(buf_i);
            offset = get_offset(buf_i);
            length = get_length(buf_i);
            *buf_o = board_post_list(bid, offset, length);
        }
        else if (!strcmp(API_name, "board_post_length")) {
            bid = get_bid(buf_i);
            *buf_o = board_post_length(bid);
        }
        else if (!strcmp(API_name, "board_inner_post_list")) {
            bid = get_bid(buf_i);
            offset = get_offset(buf_i);
            length = get_length(buf_i);
            *buf_o = board_inner_post_list(bid, offset, length);
        }
        else if (!strcmp(API_name, "board_inner_post_length")) {
            bid = get_bid(buf_i);
            *buf_o = board_inner_post_length (bid);
        }
        else if (!strcmp(API_name, "user_fav_list")) {
            uid = get_uid(buf_i);
            offset = get_offset(buf_i);
            length = get_length(buf_i);
            *buf_o = user_fav_list(uid, offset, length);
        }
        else if (!strcmp(API_name, "user_fav_list_length")) {
            uid = get_uid(buf_i);
            *buf_o = user_fav_list_length(uid);
        }
        else if (!strcmp(API_name, "board_post_path")) {
             bid = get_bid(buf_i);
             const unsigned aid_index = get_aid_index(buf_i);
            *buf_o = board_post_path(bid, aid_index);
        }
        else if (!strcmp(API_name, "class_items_list")) {
            char *cpath = get_cpath(buf_i);
            *buf_o = class_items_list(cpath);
            free(cpath);
        }
        else if (!strcmp(API_name, "utf8_test")) {
            *buf_o = utf8_test (buf_i);
        }
        else {
            fprintf(stderr, "API [%s] not found\n", API_name);
            *buf_o = NULL;
        }
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

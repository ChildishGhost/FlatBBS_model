#include "api.h"
#include "json.h"

#include <stdlib.h>
#include <string.h>

// all boards list
char *board_list (const unsigned offset, const unsigned length) {
    fprintf(stdout, "%s\n", __func__);

    return make_stub();
}

char *board_length (void) {
    fprintf(stdout, "%s\n", __func__);

    unsigned board_length = 5566;

    return make_json(50, "{ \"length\" : %d }", board_length);
}

// all posts of one board
char *board_post_list(const unsigned bid, const unsigned offset, const unsigned length) {
    fprintf(stdout, "%s\n", __func__);

    return make_stub();
}

char *board_post_length(const unsigned bid) {
    fprintf(stdout, "%s\n", __func__);

    return make_stub();
}

// all inner posts of a board
char *board_inner_post_list (const unsigned bid, const unsigned offset, const unsigned length) {
    fprintf(stdout, "%s\n", __func__);

    return make_stub();
}

char *board_inner_post_length (const unsigned bid) {
    fprintf(stdout, "%s\n", __func__);

    return make_stub();
}

// favorite boards list of a user
char *user_fav_list (const unsigned uid, const unsigned offset, const unsigned length) {
    fprintf(stdout, "%s\n", __func__);

    return make_stub();
}

char *user_fav_list_length (const unsigned uid) {
    fprintf(stdout, "%s\n", __func__);

    return make_stub();
}

// load or save a post, save if aid_index = -1
char *board_post_path (const unsigned bid, const long aid_index) {
    fprintf(stdout, "%s\n", __func__);

    return make_stub();
}

// the list of nodes belong to given class path
char *class_items_list (const char *cpath) {
    fprintf(stdout, "%s\n", __func__);

    return make_stub();
}

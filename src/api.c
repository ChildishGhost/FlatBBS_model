#include "api.h"
#include "board.h"

// all boards list
char *board_list (const unsigned offset, const unsigned length) {
    fprintf(stdout, "%s\n", __func__);

    return make_stub();
}

char *board_length (void) {
    fprintf(stdout, "%s\n", __func__);
    return make_json(50, "{ \"length\" : %d }", BRD_length());
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

char *utf8_test (const char *buf) {
    char *buf_o = (char *)malloc(sizeof(char) * 1000);
    UChar *u_str = (UChar *)malloc(sizeof(UChar) * 1000);
    UChar *u_str2 = (UChar *)malloc(sizeof(UChar) * 1000);

    u_uastrncpy (u_str, buf, 1000);
    u_printf("%s (%d) -> %S (%d)\n", buf, strnlen(buf, 100), u_str, u_strlen(u_str));

    U_STRING_DECL(fmt, "(づ｡◕‿‿◕｡)づ 抓到 API: %S", 1000);
    u_sprintf_u(u_str2, fmt, u_str);
    u_austrcpy (buf_o, u_str2);

    free(u_str);
    free(u_str2);
    return buf_o;
}

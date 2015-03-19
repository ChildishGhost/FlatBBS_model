#include "api.h"
#include "board.h"

#include <string.h>

char *board_new (const char *buf_i) {
    fprintf(stdout, "%s\n", __func__);

    char *name = get_name(buf_i);
    utf8 *category = get_category(buf_i);
    utf8 *title = get_title(buf_i);
    unsigned *masters = get_masters(buf_i);
    const unsigned masters_count = get_masters_count(buf_i);
    const enum BOARD_PERM perm = get_perm(buf_i);
    const unsigned attr = get_attr(buf_i);

    int idx = create_brd (name, category, title,
                          masters, masters_count,
                          perm, attr);
    free(name);
    free(category);
    free(title);
    free(masters);

    return make_json(50, "{ \"index\" : %d }", idx);
}

// all boards list
char *board_list (const char *buf_i) {
    fprintf(stdout, "%s\n", __func__);

    const unsigned offset = get_offset(buf_i);
    const unsigned length = get_length(buf_i);

    return make_stub();
}

char *board_length (void) {
    fprintf(stdout, "%s\n", __func__);
    return make_json(50, "{ \"length\" : %d }", BRD_length());
}

// all posts of one board
char *board_post_list(const char *buf_i) {
    fprintf(stdout, "%s\n", __func__);

    const unsigned bid = get_bid(buf_i);
    const unsigned offset = get_offset(buf_i);
    const unsigned length = get_length(buf_i);

    return make_stub();
}

char *board_post_length(const char *buf_i) {
    fprintf(stdout, "%s\n", __func__);

    const unsigned bid = get_bid(buf_i);

    return make_stub();
}

// all inner posts of a board
char *board_inner_post_list (const char *buf_i) {
    fprintf(stdout, "%s\n", __func__);

    const unsigned bid = get_bid(buf_i);
    const unsigned offset = get_offset(buf_i);
    const unsigned length = get_length(buf_i);

    return make_stub();
}

char *board_inner_post_length (const char *buf_i) {
    fprintf(stdout, "%s\n", __func__);

    const unsigned bid = get_bid(buf_i);

    return make_stub();
}

// favorite boards list of a user
char *user_fav_list (const char *buf_i) {
    fprintf(stdout, "%s\n", __func__);

    const unsigned uid = get_uid(buf_i);
    const unsigned offset = get_offset(buf_i);
    const unsigned length = get_length(buf_i);

    return make_stub();
}

char *user_fav_list_length (const char *buf_i) {
    fprintf(stdout, "%s\n", __func__);

    const unsigned uid = get_uid(buf_i);

    return make_stub();
}

// load or save a post, save if aid_index = -1
char *board_post_path (const char *buf_i) {
    fprintf(stdout, "%s\n", __func__);

    const unsigned bid = get_bid(buf_i);
    const unsigned aid_index = get_aid_index(buf_i);

    return make_stub();
}

// the list of nodes belong to given class path
char *class_items_list (const char *buf_i) {
    fprintf(stdout, "%s\n", __func__);

    char *cpath = get_cpath(buf_i);

    free(cpath);

    return make_stub();
}

char *utf8_test (const char *buf) {
    char *buf_o = (char *)malloc(sizeof(char) * 1000);
    utf8 *u_str = (utf8 *)malloc(sizeof(utf8) * 1000);
    utf8 *u_str2 = (utf8 *)malloc(sizeof(utf8) * 1000);

    u_uastrncpy (u_str, buf, 1000);
    char *param = get_param (buf);
    u_printf("%s (%d) -> %S (%d)\n", buf, strnlen(buf, 100), u_str, u_strlen(u_str));

    U_STRING_DECL(fmt, "(づ｡◕‿‿◕｡)づ 抓到 API: %S 參數：%s", 1000);
    u_sprintf_u(u_str2, fmt, u_str, param);
    u_austrcpy (buf_o, u_str2);

    free(u_str);
    free(u_str2);
    free(param);
    return buf_o;
}

#include "api.h"
#include "board.h"
#include "user.h"

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

    int idx = create_brd(name, category, title,
                         masters, masters_count,
                         perm, attr);
    free(name);
    free(category);
    free(title);
    free(masters);

    return make_json(50, "{ \"index\" : %d }", idx);
}

char *board_get (const char *buf_i) {
    fprintf(stdout, "%s\n", __func__);

    char *buf_o = NULL;
    const unsigned bid = get_bid(buf_i);
    struct BRD *brd = load_brd(bid);
    if (brd) {
        char *masters_array = board_master_array(brd);
        char *vote = vote2text(brd);
        char *perm = perm2text(brd);
        buf_o = make_json(1000, "{ \"name\" : \"%s\","
                                "  \"category\" : \"%S\","
                                "  \"title\" : \"%S\","
                                "  \"masters\" : %s,"
                                "  \"vote\" : \"%s\","
                                "  \"perm\" : \"%s\","
                                "  \"attr\" : %u,"
                                "  \"num_posts\" : %u,"
                                "  \"popular\" : %u,"
                                "  \"last_updated\" : %ld,"
                                "  \"last_post\" : %ld"
                                "}", brd->name,
                                     brd->category,
                                     brd->title,
                                     masters_array,
                                     vote,
                                     perm,
                                     brd->attr,
                                     brd->num_posts,
                                     brd->popular,
                                     brd->last_updated,
                                     brd->last_post);

        free(masters_array);
        free(vote);
        free(perm);
        free(brd);
    }
    else {
        buf_o =  make_stub();
    }

    return buf_o;
}

// all boards list
char *board_list (const char *buf_i) {
    fprintf(stdout, "%s\n", __func__);

    const unsigned offset = get_offset(buf_i);
    const unsigned length = get_length(buf_i);

    return make_stub();
}

char *board_length (const char *buf_i) {
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

// create a new user
char *user_new (const char *buf_i) {
    fprintf(stdout, "%s\n", __func__);

    // base
    char *username = get_username(buf_i);
    char *password = get_password(buf_i);
    utf8 *usernick = get_usernick(buf_i);
    char *email = get_email(buf_i);

    // extra
    const unsigned month = get_month(buf_i);
    const unsigned day = get_day(buf_i);
    const enum SEX sex = get_sex(buf_i);

    int idx = create_usr(username, password, usernick, email,
                         month, day, sex);

    free(username);
    free(password);
    free(usernick);
    free(email);

    // return uid of the created user
    // note, uid is started from 1
    return make_json(50, "{ \"index\" : %d }", idx);
}

// user elements getters
char *user_get (const char *buf_i) {
    fprintf(stdout, "%s\n", __func__);

    char *buf_o = NULL;
    const unsigned uid = get_uid(buf_i);
    struct USER_BASE *usr = load_usr(uid);

    if (usr) {
        char *perm_cstr = usr_perm2text(usr);
        char *sex_cstr = usr_sex2text(usr);
        buf_o = make_json(1000, "{ \"username\"    : \"%s\", "
                                "  \"password\"    : \"%s\", "
                                "  \"usernick\"    : \"%S\", "
                                "  \"from\"        : \"%S\", "
                                "  \"perm\"        : \"%s\", "
                                "  \"ufo\"         :   %u,   "
                                "  \"signature\"   :   %u,   "
                                "  \"num_logins\"  :   %u,   "
                                "  \"num_posts\"   :   %u,   "
                                "  \"good_article\":   %u,   "
                                "  \"bad_article\" :   %u,   "
                                "  \"first_login\" :   %ld,  "
                                "  \"last_login\"  :   %ld,  "
                                "  \"staytime\"    :   %lld, "
                                "  \"email\"       : \"%s\", "
                                "  \"month\"       :   %d,   "
                                "  \"day\"         :   %d,   "
                                "  \"sex\"         : \"%s\", "
                                "  \"money\"       :   %u,   "
                                "  \"gold\"        :   %u    "
                                "}", usr->username,
                                     usr->password,
                                     usr->usernick,
                                     usr->from,
                                     perm_cstr,
                                     usr->ufo,
                                     usr->signature,
                                     usr->num_logins,
                                     usr->num_posts,
                                     usr->good_article,
                                     usr->bad_article,
                                     usr->first_login,
                                     usr->last_login,
                                     usr->staytime,
                                     usr->email,
                                     usr->extra.month,
                                     usr->extra.day,
                                     sex_cstr,
                                     usr->extra.money,
                                     usr->extra.gold);

        free(perm_cstr);
        free(sex_cstr);
    }
    else {
        buf_o = make_stub();
    }

    return buf_o;
}

// all users' list
//TODO: char *user_list (const char *);

char *user_length (const char *buf_i) {
    fprintf(stdout, "%s\n", __func__);
    return make_json(50, "{ \"length\" : %d }", USR_length());
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


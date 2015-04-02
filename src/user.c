#include "user.h"

unsigned user_name2uid (const char *username) {
    if (!username) {
        return 0;
    }

    // TODO: return USER_BASE.uid
    return 5566;
}


char *user_uid2name (const unsigned uid) {
    char *username = (char *)malloc(20);
    if (username) {
        if (!uid) {
            strncpy(username, "", 20);
        }
        else {
            // TODO: return USER_BASE.username
            strncpy(username, "stub", 20);
        }
    }

    return username;
}

int create_usr (const char *username, const char *password,
                const utf8 *usernick, const char *email,
                const unsigned month, const unsigned day, const enum SEX sex) {

    struct USER_BASE *new_usr = (struct USER_BASE *)malloc(sizeof(struct USER_BASE));
    int idx = -1;

    if (new_usr) {
        // base
        memcpy(new_usr->username, username, member_size(struct USER_BASE, username));
        memcpy(new_usr->password, password, member_size(struct USER_BASE, password));
        memcpy(new_usr->usernick, usernick, member_size(struct USER_BASE, usernick));
        // TODO new_usr->from = user ip;
        U_STRING_DECL(fmt, "測試故鄉", member_size(struct USER_BASE, from));
        u_sprintf_u(new_usr->from, fmt);


        new_usr->perm = PERM_USER;
        new_usr->ufo = 0;
        new_usr->signature = 0;

        new_usr->num_logins = 0;
        new_usr->num_posts = 0;
        new_usr->good_article = 0;
        new_usr->bad_article = 0;

        new_usr->first_login = time(NULL);
        new_usr->last_login = time(NULL);
        new_usr->staytime = 0ULL;

        memcpy(new_usr->email, email, member_size(struct USER_BASE, email));
        // TODO user log initialize

        // extra
        new_usr->extra.month = month;
        new_usr->extra.day = day;
        new_usr->extra.sex = sex;
        new_usr->extra.money = 0;
        new_usr->extra.gold = 0;

        idx = USR_length();
        idx = save_usr(new_usr, idx);
        new_usr->uid = idx;

        free(new_usr);
    }

    return idx;
}

// usr must not be null
// without system write permission, function will fall into infinite loop
int save_usr (struct USER_BASE *usr, int idx) {
    if (!usr)
        return -1;


    FILE *fp = fopen(USR_PATH, "rb+");
    if (fp) {
        idx = write_struct_from_file(usr, sizeof(struct USER_BASE), idx, fp);
        fclose(fp);
    }
    else {
        fprintf(stderr, "error on fopen() in %s\n", __func__);
        // hack: rb+ mode requires the existence of the file, just touch one
        FILE *t = fopen(USR_PATH, "ab");
        if (t) {
            fclose(t);
        }
        save_usr(usr, idx);
    }
    return idx;
}

int USR_length (void) {
    int user_length = 0;

    FILE *fp = fopen(USR_PATH, "rb");
    if (fp) {
        user_length = struct_count_of_file(sizeof(struct USER_BASE), fp);
        fclose(fp);
    }

    // user id must start from 1
    user_length = user_length == 0 ? 1 : user_length;

    return user_length;
}

// load a user structure from USR[idx]
struct USER_BASE *load_usr (int idx) {
    if (idx == -1)
        return NULL;

    struct USER_BASE *usr = (struct USER_BASE *)malloc(sizeof(struct USER_BASE));

    if (usr) {
        FILE *fp = fopen(USR_PATH, "rb");
        if (fp) {
            usr = read_struct_from_file(sizeof(struct USER_BASE), idx, fp);
            fclose(fp);
        }
    }

    return usr;
}

char *usr_perm2text (struct USER_BASE *usr) {
    char *perm = (char *)malloc(10);

    switch (usr->perm) {
        case PERM_SYSOP:
            strcpy(perm, "sysop");
            break;
        case PERM_ADMIN:
            strcpy(perm, "admin");
            break;
        case PERM_USER:
            strcpy(perm, "user");
            break;
        case PERM_BOT:
            strcpy(perm, "bot");
            break;
        default:
            strcpy(perm, "guest");
    }

    return perm;
}

char *usr_sex2text (struct USER_BASE *usr) {
    char *sex = (char *)malloc(10);
    switch (usr->extra.sex) {
        case SEX_MALE:
            strcpy(sex, "male");
            break;
        case SEX_FEMALE:
            strcpy(sex, "female");
            break;
        default:
            strcpy(sex, "unknown");
    }
    return sex;
}


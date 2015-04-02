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

// return value: uid
int create_usr(const utf8 *username, const char *password, const utf8 *usernick,
               const char *email, const unsigned mounth, const unsigned day, const enum SEX sex) {
    struct USER_BASE *new_usr = (struct USER_BASE *)malloc(sizeof(struct USER_BASE)) ;
    int idx = -1 ;
    if (new_usr) {
        memcpy(new_usr->username, username, member_size(struct USER_BASE, username)) ;
        memcpy(new_usr->password, password, member_size(struct USER_BASE, password)) ;
        memcpy(new_usr->usernick, usernick, member_size(struct USER_BASE, usernick)) ;
        memcpy(new_usr->email, email, member_size(struct USER_BASE, email)) ;
        new_usr->extra.mounth = mounth ;
        new_usr->extra.day = day ;
        new_usr->extra.sex = sex ;
         
        new_usr->from = NULL ;
        new_usr->perm = PERM_USER ;
        // ufo initialize ??
        new_usr->signature = 0 ; // default signature file number
        new_usr->num_logins = 0 ;
        new_usr->num_posts = 0 ;
        new_usr->good_article = 0 ;
        new_usr->bad_article = 0 ;
        new_usr->first_login = time(NULL) ;
        new_usr->last_login = time(NULL) ;
        new_usr->staytime = 0ULL ;
        // log initialize ??
        new_usr->extra.money = 0 ;
        new_usr->extra.gold = 0 ;

        idx = USR_length() ;
        idx = save_usr(new_usr, idx) ;

        free(new_usr) ;
    }

    return idx ;
}


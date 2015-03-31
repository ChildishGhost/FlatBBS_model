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

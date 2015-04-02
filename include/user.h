#include "struct.h"

#ifndef USER_H
#define USER_H

unsigned user_name2uid (const char *);
char *user_uid2name (const unsigned);

int create_usr(const utf8 *, const char *, const utf8 *,
               const char *, const unsigned, const unsigned, const enum SEX) ;

int save_usr(struct USER_BASE *, int) ;

int USR_length(void) ;

#endif /* USER_H */

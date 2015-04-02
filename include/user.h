#include "struct.h"

#ifndef USER_H
#define USER_H

unsigned user_name2uid (const char *);
char *user_uid2name (const unsigned);

int create_usr(const char *, const char *, const utf8 *,
               const char *, const unsigned, const unsigned, const enum SEX) ;

int save_usr(struct USER_BASE *, int) ;

struct USER_BASE *load_usr(int) ;

int USR_length(void) ;

char *usr_perm2text(struct USER_BASE *) ;
char *usr_sex2text (struct USER_BASE *) ;

#endif /* USER_H */

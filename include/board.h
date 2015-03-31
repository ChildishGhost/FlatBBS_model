#include "struct.h"
#include "user.h"

#ifndef BOARD_H
#define BOARD_H

int create_brd (const char *, const utf8 *, const utf8 *, const unsigned *,
                  const unsigned, const enum BOARD_PERM, const unsigned);

int save_brd (struct BRD *, int);
struct BRD *load_brd (int);
int BRD_length (void);
char *board_master_array (struct BRD *);
char *vote2text (struct BRD *);
char *perm2text (struct BRD *);

#endif /* BOARD_H */

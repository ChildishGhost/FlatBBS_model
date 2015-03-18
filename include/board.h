#include "struct.h"

#ifndef BOARD_H
#define BOARD_H

#define BRD_PATH "../../data/BRD"

int create_brd (const char *, const utf8 *, const utf8 *, const unsigned *,
                  const unsigned, const enum BOARD_PERM, const unsigned);

int save_brd (struct BRD *, int);
struct BRD *load_board (int);
int BRD_length (void);

#endif /* BOARD_H */

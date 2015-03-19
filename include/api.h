#include "struct.h"

#include "json.h"

#include <stdlib.h>
#include <string.h>

#ifndef API_H
#define API_H

// all boards list
char *board_list (const unsigned, const unsigned);
char *board_length (void);

// all posts of one board
char *board_post_list (const unsigned, const unsigned, const unsigned);
char *board_post_length (const unsigned );

// all inner posts of a board
char *board_inner_post_list (const unsigned, const unsigned, const unsigned);
char *board_inner_post_length (const unsigned);

// favorite boards list of a user
char *user_fav_list (const unsigned, const unsigned, const unsigned);
char *user_fav_list_length (const unsigned);

// load or save a post, save if aid_index = -1
char *board_post_path (const unsigned, const long);

// the list of nodes belong to given class path
char *class_items_list (const char *);

// UTF8 testing
char *utf8_test (const char *);

#endif /* API_H */

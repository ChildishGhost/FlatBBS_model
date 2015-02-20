#include "struct.h"


#ifndef API_H
#define API_H

// all boards list
char *board_list (const unsigned offset, const unsigned length);
char *board_length (void);

// all posts of one board
char *board_post_list(const unsigned bid, const unsigned offset, const unsigned length);
char *board_post_length(const unsigned bid);

// all inner posts of a board
char *board_inner_post_list(const unsigned bid, const unsigned offset, const unsigned length);
char *board_inner_post_length(const unsigned bid);

// favorite boards list of a user
char *user_fav_list (const unsigned uid, const unsigned offset, const unsigned length);
char *user_fav_list_length (const unsigned uid);

// load or save a post, save if aid_index = -1
char *board_post_path(const unsigned bid, const long aid_index);

// the list of nodes belong to given class path
char *class_items_list(const char *cpath);


#endif /* API_H */

#include "struct.h"
#include "user.h"

#include <jansson.h>

#include <stdarg.h>
#include <string.h>

#ifndef JSON_H
#define JSON_H

// json utilities, wrappers for the jansson library
//
// pack/unpack JSON between data
//
// all interface should be C types like int or char * or utf8 *

// board
unsigned get_bid (const char *);
char *get_name (const char *);
utf8 *get_category (const char *);
utf8 *get_title (const char *);
unsigned *get_masters (const char *);
unsigned get_masters_count (const char *);
enum BOARD_PERM get_perm (const char *);
unsigned get_attr(const char *);

// user
unsigned get_uid (const char *);
char *get_username (const char *);
char *get_password (const char *);
utf8 *get_usernick (const char *);
char *get_email (const char *);
unsigned get_month (const char *);
unsigned get_day (const char *);
enum SEX get_sex (const char *);

// post

// class
unsigned get_aid_index (const char *);
char *get_cpath (const char *);

// test
char *get_param (const char *);

// utilities
char *get_API_name (const char *);
unsigned get_offset(const char *);
unsigned get_length(const char *);
char *make_stub (void);
char *make_json (unsigned, const char *, ...);

#endif /* JSON_H */

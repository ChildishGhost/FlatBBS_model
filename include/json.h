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
char *get_name (const char *);
utf8 *get_category (const char *);
utf8 *get_title (const char *);
unsigned *get_masters (const char *);
unsigned get_masters_count (const char *);

// test
char *get_param (const char *);

// utilities
char *get_API_name (const char *);
char *make_stub (void);
char *make_json (unsigned, const char *, ...);

#endif /* JSON_H */

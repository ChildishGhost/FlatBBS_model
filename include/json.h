#include "struct.h"

#include <jansson.h>

#include <stdarg.h>
#include <string.h>

#ifndef JSON_H
#define JSON_H

// json utilities, wrappers for the jansson library
//
// all interface should be C types like int or char *

char *get_API_name (const char *buf_i);

char *make_stub (void);
char *make_json (unsigned, const char *, ...);

#endif /* JSON_H */

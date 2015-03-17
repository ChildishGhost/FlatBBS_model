#include "struct.h"

#include <jansson.h>

#include <string.h>

#ifndef JSON_H
#define JSON_H

// json utilities, wrappers for the jansson library
//
// all interface should be C types like int or char *

// shortcuts for jansson APIs
json_t     *(*_get)(const json_t *, const char *) = json_object_get;
const char *(*_s)(const json_t *) = json_string_value;
size_t      (*_s_len)(const json_t *) = json_string_length;
json_int_t  (*_i)(const json_t *) = json_integer_value;
double      (*_r)(const json_t *) = json_real_value;

json_t *json_ctor (const char *text) {

    // TODO: add needed flags and error handling code here
    json_error_t error;
    json_t *root = json_loads(text, 0, &error);

    return json_is_null(root) ? NULL : root;
}

// alias of ref--
void json_dtor (json_t *j) {
    json_decref(j);
}

// get API name from JSON: { "api" : "name" , ...}
char *get_API_name (const char *buf_i) {

    json_t *root = json_ctor(buf_i);

    const char *str  = _s(_get(root, "api"));
    size_t sz = _s_len(_get(root, "api"));

    char *name = (char *)malloc(sz + 1);

    if (name) {
        memcpy(name, str, sz);
        name[sz] = '\0';
    }

    json_dtor(root);
    return name;
}

#endif /* JSON_H */

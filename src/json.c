#include "json.h"

// shortcuts for jansson APIs
static json_t     *(*_get)(const json_t *, const char *) = json_object_get;
static const char *(*_s)(const json_t *) = json_string_value;
static size_t      (*_s_len)(const json_t *) = json_string_length;
static json_int_t  (*_i)(const json_t *) = json_integer_value;
static double      (*_r)(const json_t *) = json_real_value;

static json_t *json_ctor (const char *text) {

    // TODO: add needed flags and error handling code here
    json_error_t error;
    json_t *root = json_loads(text, 0, &error);

    return json_is_null(root) ? NULL : root;
}

// alias of ref--
static void json_dtor (json_t *j) {
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

// empty json stub for testing
char *make_stub (void) {

    char *buf = malloc(10);
    if (buf)
        strcpy(buf, "{ }");

    return buf;
}

// allocate a fixed size json string with parameters
char *make_json (unsigned sz, const char *fmt, ...) {

    char *buf = malloc(sz);
    if (buf) {
        va_list ap;
        va_start(ap, fmt);
        vsprintf(buf, fmt, ap);
        va_end(ap);
    }
    return buf;
}

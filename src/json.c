#include "json.h"

// shortcuts for jansson APIs
static json_t     *(*_get)(const json_t *, const char *) = json_object_get;
static const char *(*_s)(const json_t *) = json_string_value;
static size_t      (*_s_len)(const json_t *) = json_string_length;
static json_int_t  (*_i)(const json_t *) = json_integer_value;
static double      (*_f)(const json_t *) = json_real_value;

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

static char *_json_get_string (const char *buf_i, const char *key) {
    json_t *root = json_ctor(buf_i);

    const char *str  = _s(_get(root, key));
    size_t sz = _s_len(_get(root, key));

    char *value = (char *)malloc(sz + 1);

    if (value) {
        memcpy(value, str, sz);
        value[sz] = '\0';
    }

    json_dtor(root);
    return value;
}

static long long _json_get_integer (const char *buf_i, const char *key) {
    json_t *root = json_ctor(buf_i);

    int value = _i(_get(root, key));

    json_dtor(root);
    return value;
}

static long long _json_get_floating (const char *buf_i, const char *key) {
    json_t *root = json_ctor(buf_i);

    int value = _f(_get(root, key));

    json_dtor(root);
    return value;
}

char *get_param (const char *buf_i) {
    return _json_get_string(buf_i, "param");
}

// get API name from JSON: { "api" : "name" , ...}
char *get_API_name (const char *buf_i) {
    return _json_get_string(buf_i, "api");
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

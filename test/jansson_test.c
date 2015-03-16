#include <string.h>
#include <jansson.h>
#include <uchar.h>
#include "struct.h"


// this is the test program for Jansson APIs
// Ref: http://jansson.readthedocs.org/en/latest/apiref.html
//
//
// compile: clang -O2 -std=c11 -I../include jansson_test.c -ljansson
//
//
// jasson will crash or return incorrect results in the following case:
//
//   1. intergers starts leading zero, like 05566
//   2. floats starts leading dot, like .5566
//
//
// Usage:
//
//   types:
//
//       json_t: the json object
//       json_int_t: long long
//
//   functions:
//
//       json_array_get(const json_t *, size_t) -> json_t *
//       json_object_get(const json_t *, const char *) -> json_t *
//
//       json_string_value(const json_t *) -> const char *
//       json_integer_value(const json_t *) -> json_int_t
//       json_real_value(const json_t *) -> double
//
//
//       json_array_size(const json_t *) -> size_t
//       json_object_size(const json_t *) -> size_t

int main (void) {
    json_t *root;
    json_error_t error;

    // example stolen from here: http://json.org/example
     char text[] =
         "{"
         "    \"glossary\": {"
         "        \"title\": \"example glossary\\\"\","
         "        \"GlossDiv\": {"
         "            \"title\": \"double five, double six\","
         "            \"GlossList\": {"
         "                \"GlossEntry\": {"
         "                    \"ID\": \"SGML\","
         "                    \"SortAs\": \"SGML\","
         "                    \"GlossTerm\": \"Standard Generalized Markup Language\","
         "                    \"Acronym\": \"SGML\","
         "                    \"Abbrev\": \"ISO 8879:1986\","
         "                    \"GlossDef\": {"
         "                        \"para\": \"A meta-markup language, used to create markup languages such as DocBook.\","
         "                        \"GlossSeeAlso\": [\"GML\", \"XML\"]"
         "                    },"
         "                    \"GlossSee\": \"markup\""
         "                }"
         "            }"
         "        }"
         "    },"
         "  \"integer\" : 5566,"
         "  \"real\" : 0.5566,"
         "  \"中文\" : \"測試\""
         "}";
         ;


    root = json_loads(text, 0, &error);

    // define some shortcuts
    json_t     *(*_get)(const json_t *, const char *) = json_object_get;
    const char *(*_s)(const json_t *) = json_string_value;
    json_int_t  (*_i)(const json_t *) = json_integer_value;
    double      (*_r)(const json_t *) = json_real_value;

    if (!json_is_null(root)) {
        printf("%s == double five, double six\n", _s(_get(_get(_get(root, "glossary"), "GlossDiv"), "title")));
        printf("%lld == 5566\n", _i(_get(root, "integer")));
        printf("%f == 0.5566\n", _r(_get(root, "real")));
        printf("%s == 測試\n", _s(_get(root, "中文")));


        json_t *t = _get(_get(_get(_get(_get(_get(root, "glossary"), "GlossDiv"), "GlossList"), "GlossEntry"), "GlossDef"), "GlossSeeAlso");
        printf("%d == 2\n", (int)json_array_size(t));

    }

    return 0;

}

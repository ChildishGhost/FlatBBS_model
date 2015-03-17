# some docs about json

## JSON utilities

We put the JSON utilities in `include/json.h`

This is a wrapper to `jansson` library, all JSON related operations should be

done here

### design and interface

`json.h` offers JSON pack/unpack operations, all the functions should be designed

as the following rules:

1. keep all (external) interfaces with C types, such as `int` or `char *`
2. getters should be named as `get_xxx`
3. a function should return `char *` if there's only a string
4. other return values are returned by pointers
5. all parameters except used for return values should be `const` protected
6. callers should free the memory allocated by inside functions here
7. internal stuffs should be `static`



## Library

We are using jansson lib

Installation: `sudo pacman -S jansson`

Ref: [API Ref](http://jansson.readthedocs.org/en/latest/apiref.html)


## notes

jasson will crash or return incorrect results in the following case:

  1. intergers starts leading zero, like 05566
  2. floats starts leading dot, like .5566



## Usage

### types

```
    json_t: the json object
    json_int_t: long long
```

### functions

```
    json_array_get(const json_t *, size_t) -> json_t *
    json_object_get(const json_t *, const char *) -> json_t *

    json_string_value(const json_t *) -> const char *
    json_integer_value(const json_t *) -> json_int_t
    json_real_value(const json_t *) -> double


    json_array_size(const json_t *) -> size_t
    json_object_size(const json_t *) -> size_t
```

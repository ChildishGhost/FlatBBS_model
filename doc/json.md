# some docs about json

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

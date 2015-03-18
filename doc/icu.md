# some docs about unicode

## Unicode utilities

Currently used only in `struct.h`, other utilities should have its own wrappers
for their structures

- `struct.h` is now using the following headers:
- we have an alias to `UChar`, we should use `utf8` in all other places

```
#include <unicode/ustdio.h>
#include <unicode/ustring.h>

typedef UChar utf8;
```


## Library

We are using ICU - International Components for Unicode

Installation: `sudo pacman -S icu`

Ref: [API Ref](https://ssl.icu-project.org/apiref/icu4c/)


## types

- `UChar *` represents a pointer to a Unicode string

- `char *` represents a pointer to a C string (raw data)

- `sizeof(UChar) == 2` (on my machine)

- `sizeof(char) == 1` (C standard)


## string literals

declare and initialize a Unicode string literal

the length of the string, not including the terminating `NUL`, must be specified as a constant

`U_STRING_INIT` seems not work

```
    U_STRING_DECL(name, string literal, length);

    U_STRING_DECL(ptt, "五六不能亡", 30);
```

## allocation and deallocation

just take them as normal `char *`

```
   // allocate UChar[10]
   UChar *str = (UChar *)malloc(sizeof(UChar) * 10);
   free(str);
```

## common functions

### `#include <unicode/ustdio.h>`

```

// print to stdout
int32_t u_printf (const char *fmt,...)
int32_t u_printf_u (const UChar *fmt,...)

// print to Unicode string with C string formatter
int32_t u_sprintf (UChar *buffer, const char *fmt,...)
int32_t u_snprintf (UChar *buffer, int32_t count, const char *fmt,...)

// print to Unicode string with Unicode formatter
int32_t u_sprintf_u (UChar *buffer, const UChar *fmt,...)
int32_t u_snprintf_u (UChar *buffer, int32_t count, const UChar *fmt,...)
```

### `#include <unicode/ustring.h>`

```

// just like strlen, null terminator is not included
int32_t u_strlen (const UChar *s)

// cat two Unicode strings
UChar  *u_strcat (UChar *dst, const UChar *src)
UChar  *u_strncat (UChar *dst, const UChar *src, int32_t n)

// copy two Unicode strings
UChar  *u_strcpy (UChar *dst, const UChar *src)
UChar  *u_strncpy (UChar *dst, const UChar *src, int32_t n)

// copy C string to Unicode string
UChar  *u_uastrcpy (UChar *dst, const char *src)
UChar  *u_uastrncpy (UChar *dst, const char *src, int32_t n)

// copy Unicode string to C string
char *  u_austrcpy (char *dst, const UChar *src)
char *  u_austrncpy (char *dst, const UChar *src, int32_t n)

```

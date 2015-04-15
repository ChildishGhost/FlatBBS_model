#include "struct.h"

#include <unicode/ustring.h>
#include <unicode/ustdio.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct FOO {
    char name[10];
    UChar nick[20];
};

// testing for ICU
// compile: clang -O2 -std=c11 -I../include `pkg-config --libs --cflags icu-uc icu-io` icu_test.c

int main (void) {

    const char *foo = "ＧＧ硬硬der";
    puts("converting between char * and UChar * with u_*strcpy");
    UChar *dst = (UChar *)malloc(sizeof(UChar) * 10);
    u_uastrcpy (dst, foo);
    u_printf("cpy C->U %S %d\n", dst, u_strlen(dst));

    char *bar = (char *)malloc(sizeof(char) * 50);
    u_austrcpy (bar, dst);
    printf("cpy U->C %s %lu\n", bar, strlen(bar));


    puts("write/read file test");
    FILE *f = fopen("gg", "w");
    fputs(bar, f);
    fclose(f);

    free(bar);
    bar = NULL;

    bar = (char *)malloc(sizeof(char) * 50);
    f = fopen("gg", "r");
    fgets(bar, 100, f);
    puts("char *");
    printf("%s %lu\n", bar, strlen(bar));
    u_uastrcpy (dst, bar);
    puts("UChar *");
    u_printf("%S %d\n", dst, u_strlen(dst));
    fclose(f);
    system("rm gg");


    free(dst);
    free(bar);


    return 0;
}

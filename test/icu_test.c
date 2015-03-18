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


    puts("structure file write/read test");
    U_STRING_DECL(fmt, "工具人 %d 號四我", 30);
    f = fopen("qq", "w");
    for (int i = 0; i < 10; i++) {
        struct FOO *foo = (struct FOO *)malloc(sizeof(struct FOO));
        sprintf(foo->name, "tool %d", i);
        u_sprintf_u(foo->nick, fmt, i);
        _write_struct_from_file (foo, sizeof(struct FOO), i, f);
        free(foo);
    }
    fclose(f);

    f = fopen("qq", "r");
    for (int i = 0; i < 10; i++) {
        struct FOO *foo = (struct FOO *)_read_struct_from_file (sizeof(struct FOO), i, f);
        u_printf("[%s] : %S\n", foo->name, foo->nick);
        free(foo);
    }
    fclose(f);

    puts("randomly fseek");
    srand(time(0));
    f = fopen("qq", "r");
    for (int i = 0; i < 1000000; i++) {
        unsigned r = ((rand() % 10) +i) % 10;
        printf("# %d foo[%d]: ", i, r);
        struct FOO *foo = (struct FOO *)_read_struct_from_file (sizeof(struct FOO), r, f);
        u_printf("[%s] : %S\n", foo->name, foo->nick);
        fflush(stdout);
        free(foo);
    }
    fclose(f);

    return 0;
}

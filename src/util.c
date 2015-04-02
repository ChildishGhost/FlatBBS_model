#include "util.h"

unsigned char *md5str (const char *buf_i, int len) {

    if (len < 0) {
        return NULL;
    }

    MD5_CTX c;
    unsigned char *buf_o = (unsigned char *)malloc(MD5_DIGEST_LENGTH);

    if (buf_o) {
        MD5_Init(&c);

        while (len > 0) {
            MD5_Update(&c, buf_i, len > 512 ? 512 : len);
            len -= 512;
            buf_i += 512;
        }

        MD5_Final(buf_o, &c);
    }
    return buf_o;
}

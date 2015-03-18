#include "struct.h"

// read a structure of an array stored in the given file
// returning array[index] stored at file[sz * index]
// sz  : must be sizeof(struct FOO)
// index : index of the needed structure in the array
// file : file descriptor
void *read_struct_from_file (size_t sz, unsigned index, FILE *file) {

    void *obj = malloc(sz);
    if (!sz || !file || !obj) {
        fprintf(stderr,"error in %s\n", __func__);
        return NULL;
    }

    if (fseek(file, sz * index, SEEK_SET)) {
        if (ferror(file)) {
            fprintf(stderr,"error on fseek() in %s\n", __func__);
            return NULL;
        }
    }


    if (fread(obj, sz, 1, file) != 1) {
        fprintf(stderr,"error on fread() in %s\n", __func__);
        return NULL;
    }

    return obj;
}

// similar to _read_struct_from_file, take an object and write that to the file
// returning index if write successfully or -1 on error
int write_struct_from_file (void *obj, size_t sz, unsigned index, FILE *file) {
    if (!sz || !file || !obj) {
        fprintf(stderr,"error in %s\n", __func__);
        return -1;
    }

    if (fseek(file, sz * index, SEEK_SET)) {
        if (ferror(file)) {
            fprintf(stderr,"error on fseek() in %s\n", __func__);
            return -1;
        }
    }


    if (fwrite(obj, sz, 1, file) != 1) {
        fprintf(stderr,"error on fwrite() in %s\n", __func__);
        return -1;
    }

    return index;

}

// sz  : must be sizeof(struct FOO)
// file : file descriptor
// returng the size of structure[] in the file
//
// note: might not work with file > 2G
// Ref: https://stackoverflow.com/questions/16696297/ftell-at-a-position-past-2gb
int struct_count_of_file (size_t sz, FILE *file) {
    if (!sz || !file) {
        fprintf(stderr,"error in %s\n", __func__);
        return -1;
    }

    if (fseek (file, 0, SEEK_END)) {
        if (ferror(file)) {
            fprintf(stderr,"error on fseek() in %s\n", __func__);
            return -1;
        }
    }

    long size = 0;

    if ((size = ftell (file)) == -1) {
        fprintf(stderr,"error on ftellk() in %s\n", __func__);
        return -1;
    }

    return size / sz;

}


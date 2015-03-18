#include "board.h"

// returning the index of the new board in BRD
int create_brd (const char *name, const utf8 *category, const utf8 *title,
                  const unsigned *masters, const unsigned masters_count,
                  const enum BOARD_PERM perm, const unsigned attr) {

    struct BRD *new_brd = (struct BRD *)malloc(sizeof(struct BRD));
    int idx = -1;

    if (new_brd) {
        strncpy(new_brd->name, name, 15);
        u_strncpy(new_brd->category, category, 10);
        u_strncpy(new_brd->title, title, 50);
        memcpy(new_brd->masters, masters, masters_count);
        new_brd->masters_count = masters_count;
        new_brd->vote = VOTE_NONE;
        new_brd->perm = perm;
        new_brd->attr = 0;
        new_brd->num_posts = 0;
        new_brd->popular = 0;
        new_brd->last_updated = time(NULL);
        new_brd->last_post = (time_t)0;

        idx = BRD_length() + 1;
        idx = save_brd(new_brd, idx);

        free(new_brd);
    }

    return idx;
}

// save a brd structure to BRD[idx]
// return index for -1 on error
int save_brd (struct BRD *brd, int idx) {
    if (idx == -1)
        return -1;

    FILE *fp = fopen(BRD_PATH, "w");
    if (fp) {
        idx = write_struct_from_file (brd, sizeof(struct BRD), idx, fp);
        fclose(fp);
    }

    return idx;
}

// load a brd structure from BRD[idx]
// return index for -1 on error
struct BRD *load_brd (int idx) {
    if (idx == -1)
        return NULL;

    struct BRD *brd = (struct BRD *)malloc(sizeof(struct BRD));

    FILE *fp = fopen(BRD_PATH, "r");
    if (fp) {
        brd = read_struct_from_file (sizeof(struct BRD), idx, fp);
        fclose(fp);
    }

    return brd;
}

int BRD_length (void) {
    int board_length = 0;

    FILE *fp = fopen(BRD_PATH, "r");
    if (fp) {
        board_length = struct_count_of_file(sizeof(struct BRD), fp);
        fclose(fp);
    }

    return board_length;
}

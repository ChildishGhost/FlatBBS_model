#include "board.h"

// returning the index of the new board in BRD
int create_brd (const char *name, const utf8 *category, const utf8 *title,
                  const unsigned *masters, const unsigned masters_count,
                  const enum BOARD_PERM perm, const unsigned attr) {

    struct BRD *new_brd = (struct BRD *)malloc(sizeof(struct BRD));
    int idx = -1;

    if (new_brd) {
        memcpy(new_brd->name, name, member_size(struct BRD, name));
        memcpy(new_brd->category, category, member_size(struct BRD, category));
        memcpy(new_brd->title, title, member_size(struct BRD, title));
        memcpy(new_brd->masters, masters, member_size(struct BRD, masters));
        new_brd->masters_count = masters_count;
        new_brd->vote = VOTE_NONE;
        new_brd->perm = perm;
        new_brd->attr = attr;
        new_brd->num_posts = 0;
        new_brd->popular = 0;
        new_brd->last_updated = time(NULL);
        new_brd->last_post = (time_t)0;

        idx = BRD_length();
        idx = save_brd(new_brd, idx);

        free(new_brd);
    }

    return idx;
}

// save a brd structure to BRD[idx]
// return index for -1 on error
int save_brd (struct BRD *brd, int idx) {
    if (!brd || idx == -1)
        return -1;

    FILE *fp = fopen(BRD_PATH, "rb+");
    if (fp) {
        idx = write_struct_from_file(brd, sizeof(struct BRD), idx, fp);
        fclose(fp);
    }
    else {
        fprintf(stderr,"error on fopen() in %s\n", __func__);
        // hack: rb+ mode requires the existence of the file, just touch one
        system("touch " BRD_PATH);
        save_brd(brd, idx);
    }

    return idx;
}

// load a brd structure from BRD[idx]
// return index for -1 on error
struct BRD *load_brd (int idx) {
    if (idx == -1)
        return NULL;

    struct BRD *brd = (struct BRD *)malloc(sizeof(struct BRD));

    if (brd) {
        FILE *fp = fopen(BRD_PATH, "rb");
        if (fp) {
            brd = read_struct_from_file(sizeof(struct BRD), idx, fp);
            fclose(fp);
        }
    }

    return brd;
}

int BRD_length (void) {
    int board_length = 0;

    FILE *fp = fopen(BRD_PATH, "rb");
    if (fp) {
        board_length = struct_count_of_file(sizeof(struct BRD), fp);
        fclose(fp);
    }
    return board_length;
}

// return a JSON array of usernames in text form
char *board_master_array (struct BRD *brd) {
    char *array = (char *)malloc(40 * member_length(struct BRD, masters, unsigned));

    if (array) {
        unsigned i = 0;
        char buf[40];
        char *username = NULL;
        sprintf(array, "[ ");
        for (i = 0; (i < brd->masters_count - 1) &&
                    (i < member_length(struct BRD, masters, unsigned)); i++) {
            username = user_uid2name(brd->masters[i]);
            if (username) {
                sprintf(buf, "\"%s\", ", username);
                strncat(array, buf, strlen(buf));
            }
            free(username);
        }
        username = user_uid2name(brd->masters[i]);
        if (username) {
            sprintf(buf, "\"%s\", ", username);
            strncat(array, buf, strlen(buf));
        }
        free(username);
        strncat(array, " ]", 2);
    }
    return array;
}

// vote status in text form
char *vote2text (struct BRD *brd) {
    char *vote = (char *)malloc(member_length(struct BRD, vote, enum VOTE_STATUS));
    if (vote) {
        if (brd->vote == VOTE_VOTEING)
            sprintf(vote, "voting");
        else if (brd->vote == VOTE_ROULETTE)
            sprintf(vote, "roulette");
        else
            sprintf(vote, "none");
    }
    return vote;
}


// board perm in text form
char *perm2text (struct BRD *brd) {
    char *perm = (char *)malloc(member_length(struct BRD, perm, enum BOARD_PERM));
    if (perm) {
        if (brd->perm == BOARD_PRIVATE)
            sprintf(perm, "private");
        else if (brd->perm == BOARD_SECRET)
            sprintf(perm, "secret");
        else
            sprintf(perm, "public");
    }
    return perm;
}

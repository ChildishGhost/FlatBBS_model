#include <stdio.h>
#include <time.h>
#include <uchar.h>

// TODO: need some wrappers of mb* functions to higher order operations
typedef char32_t utf8;

// ------------------------------------------+
// user related structures and enumerators   |
// ------------------------------------------+
// all user data will be stored to a file named USR
//
// directory layout:
//
// USR
// usr/<username>/blah blah        // user related info here
//               /USER_READ        // the unread alert system

// example of log:
// [<time>][<IP>][<FQDN>]: <content>

struct user_log {
  time_t time;                     /* timestamp */
  char IP[50];                     /* IPv6 max = 45 */
  char FQDN[50];                   /* reverse lookup */
  char content[200];               /* log content, new line terminated */
  FILE *logfile;
};

enum SEX {
  UNKNOWN,                         /* 中性（不透露）*/
  MALE,
  FEMALE
};

enum PERMISSION {
  SYSOP,                           /* 站長 */
  ADMIN,                           /* 站務 */
  USER,
  GUEST,                           /* 未驗證完成帳號 */
  BOT                              /* 特殊權限 */
};

struct user_extra {
  unsigned char month;             /* 生日(月) */
  unsigned char day;               /* 生日(日) */
  enum SEX sex;
  unsigned money;                  /* 銀幣，基本金融單位 */
  unsigned gold;                   /* 金幣 */
};

struct user_base {
  unsigned uid;                    /* unique user ID */

  char username[20];
  char password[32];
  utf8 usernick[40];
  utf8 from[40];                   /* 故鄉 */

  enum PERMISSION perm;
  unsigned ufo;                    /* preference */
  unsigned char signature;         /* 預設簽名檔編號 (0~10)*/

  unsigned numlogins;              /* 上站次數 */
  unsigned numposts;               /* 發表次數 */
  unsigned good_article;           /* 優文 */
  unsigned bad_article;            /* 劣文 */

  time_t firstlogin;               /* 第一次上站時間 */
  time_t lastlogin;                /* 上一次上站時間 */
  unsigned long long staytime;     /* 總共停留時間 (s) */

  utf8 email[100];
  struct user_log log;
  struct user_extra extra;         /* 雜七雜八 */
};

// user (un)read alert system
struct USR_READ {
  unsigned bid;
  time_t last_read;
};

// ------------------------------------------+
// board related structures and enumerators  |
// ------------------------------------------+

enum VOTE_STATUS {                 /* 0:無投票 1:有投票 2:有賭盤 */
  NONE,
  VOTE,
  ROUTLETTE
};

enum BOARD_PERM {                  /* 公開 好友 隱版 */
  PUBLIC,
  PRIVATE,
  SECRET
};


// board header
// the .BRD file stands for an array of board headers
// the index of structures in the . BRD file gives the bid for each board
//
// the directory layout for boards
//
// BRD                                     // an array of struct BRD
// brd/<board name>/[A-Z0-9]/<AID>
//                 /inner/[A-Z0-9]/<AID>   // 精華區
//                 /inner/ blah blah blah  // implementation of inner posts
//                 /POSTS                  // post index
//                 /pinned                 // 置底文，index to POSTS
//
// For example, there are 3 posts in the board <board name>
// there will be three files under the posts directory
// three headers of the structure POST will be stred as an array.
//
//          <board name>/A/AAA
//                      /A/AAB
//                      /A/AAC
//
//                      /POSTS
//
//                      /PINindex
//                          2          this refers to POSTS[2]

struct BRD {
  char name[15];                   /* board name */
  utf8 category[10];
  utf8 title[50];

  unsigned masters[16];            /* board master’s uid */
  unsigned masters_count;          /* must <= 16 */

  enum VOTE_STATUS vote;
  enum BOARD_PERM perm;            /* 公開 好友 隱版 */
  unsigned attr;                   /* 看板屬性 */
  unsigned num_posts;              /* 共有幾篇 post */
  unsigned popular;                /* 人氣 */
  time_t last_updated;
  time_t last_post;
};


// array of POST, stored in <board name>/POSTS
struct POST {
  char AID[8];
  unsigned author;                 /* author's uid */
  time_t timestamp;
  int score;
  utf8 title[256];
};


// ------------------------------------------+
// class related structures and enumerators  |
// ------------------------------------------+

struct CLS {                       /* CLASS */
  char name[15];
  utf8 category[10];
  utf8 title[50];
};

enum NODE_TYPE {
  ROOT,
  CLASS,
  BOARD
};

//
// the class system is a tree structure
// where all internal nodes are classes, and leaves are boards
//
// we use the notation A/B/C to refer to a node
//
// for example, "1/3/2"
//
// R
//  C        - 1
//   C
//   C
//    B
//    C
//     B
//   C       - 3
//    B
//    C      - 2 (here)
//   C
//

// we will offer some apis to load the tree structure
//
// curr = get node from cpath
//
// while (child : curr->children) {
//     if (child == NUL) break;
//     list.append(
//             switch (child->type) {
//             case CLASS: class_array[child->id]{.name, .category, .title};
//             case BOARD: board_array[child->id]{.name, .category, .title};
//             }
//         )
// }
//
//     get node from cpath:
//         curr->children = malloc(sizeof(struct node) * size)

struct TREE_NODE {
  struct TREE_NODE *children;
  unsigned children_count;
  enum NODE_TYPE type;
  unsigned id;                     /* class id or board id*/
};


#include <stdio.h>
#include <time.h>
#include <uchar.h>

typedef char32_t utf8;

struct user_log {
  time_t time;                     /* timestamp */
  char IP[50];                     /* IPv6 max = 45 */
  char FQDN[50];                   /* reverse lookup */
  char content[200];               /* log content, new line terminated */
  FILE *logfile;
};

// example of log:
// [<time>][<IP>][<FQDN>]: <content>

enum SEX {
  UNKNOWN,                         /* 中性（不透露）*/
  MALE,                            /* 男性 */
  FEMALE                           /* 女性 */
};

struct user_extra {
  unsigned char month;             /* 生日(月) */
  unsigned char day;               /* 生日(日) */
  enum SEX sex;
  unsigned money;                  /* 銀幣，基本金融單位 */
  unsigned gold;                   /* 金幣 */
};

enum PERMISSION {
  SYSOP,                           /* 站長 */
  ADMIN,                           /* 站務 */
  USER,
  GUEST,                           /* 未驗證完成帳號 */
  BOT                              /* 特殊權限 */
};

struct user_base {
  unsigned userno;                 /* unique positive code */

  char userid[20];                 /* ID */
  char passwd[32];                 /* 密碼 */
  utf8 username[40];               /* 暱稱 */
  utf8 from[40];                   /* 故鄉 */

  enum PERMISSION perm;            /* 權限 */
  unsigned ufo;                    /* preference */
  unsigned char signature;         /* 預設簽名檔編號 (0~10)*/

  unsigned numlogins;              /* 上站次數 */
  unsigned numposts;               /* 發表次數 */
  unsigned good_article;           /* 優文 */
  unsigned bad_article;            /* 劣文 */

  time_t firstlogin;               /* 第一次上站時間 */
  time_t lastlogin;                /* 上一次上站時間 */
  unsigned long long staytime;     /* 總共停留時間 (s) */

  utf8 email[100];                 /* 電子信箱 */
  struct user_log log;             /* log 相關 */
  struct user_extra extra;         /* 雜七雜八 */
};


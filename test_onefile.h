#include "sqlite3.h"

struct onefile_functions {
    int (*xRandomness)(int nByte, char *zOut);
};

int sqlite3_onefile_from_c(
    /* functions the backend needs*/
    struct onefile_functions foo,
    /* whether to make the backend the default sqlite VFS */
    int mkDefault
);

#include "sqlite3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./test_onefile.h"

sqlite3 *db;

static int genRandomness(int nByte, char *zOut) {
  // lol, fills with AAAAAAAAAAAA
  memset(zOut, 'A', nByte);
  return nByte;
}

static struct onefile_functions dumb_functions = {
  genRandomness /* xRandomness */
};

int main() {
  sqlite3_onefile_from_c(dumb_functions, 1 /*mkDefault*/);
  char* str = malloc(10*sizeof(char));
  memset(str, 'B', 10);
  str[9] = '\0';
  printf("orig: %s\n", str);

  // don’t overwrite the trailing \0
  sqlite3_randomness(9*sizeof(char), str);
  // this should always print AAAAA, but maybe I’m misunderstanding how sqlite3_randomness works.
  // At least we always get the same result if we set mkDefault to 1 above,
  // which means our custom implementation genRandomness is used!
  printf("random: %s\n", str);

  int open_result = sqlite3_open_v2(
    "./mydb.sqlite",
    &db,
    SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE,
    "onefile"
  );
  printf("open_result: %s\n", sqlite3_errstr(open_result));
  char *errmsg;
  int exec_result = sqlite3_exec(
    db,                                  /* An open database */
    "BEGIN TRANSACTION;",
    NULL,  /* Callback function */
    NULL,                                    /* 1st argument to callback */
    &errmsg                              /* Error msg written here */
  );
  printf("errmsg: %s %s\n",  sqlite3_errstr(exec_result), errmsg);
  exec_result = sqlite3_exec(
    db,                                  /* An open database */
    "CREATE TABLE IF NOT EXISTS hello_ocaml(camels text);",
    NULL,  /* Callback function */
    NULL,                                    /* 1st argument to callback */
    &errmsg                              /* Error msg written here */
  );
  printf("errmsg: %s %s\n",  sqlite3_errstr(exec_result), errmsg);
  exec_result = sqlite3_exec(
    db,                                  /* An open database */
    "INSERT INTO hello_ocaml (camels) VALUES ('du Kamel');",
    NULL,  /* Callback function */
    NULL,                                    /* 1st argument to callback */
    &errmsg                              /* Error msg written here */
  );
  printf("errmsg: %s %s\n",  sqlite3_errstr(exec_result), errmsg);
  sqlite3_db_cacheflush(db);
  printf("flush success\n");
  abort();
}

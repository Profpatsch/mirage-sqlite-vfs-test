#include "./test_onefile.h"
#include "sqlite3.h"
#include <stdio.h>
#include <stdlib.h>

sqlite3 *db;

int main() {
  fs_register();
  int open_result = sqlite3_open_v2(
    "./mydb.sqlite",
    &db,
    SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE,
    "test_onefile"
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

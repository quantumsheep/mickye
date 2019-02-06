#ifndef _DB_H
#define _DB_H

#include <sqlite3.h>
#include <stdlib.h>

#include "../config.h"

#define CONFIG_DB_PATH "db_path"
#define CONFIG_DB_PATH_DEFAULT "reg.db"

typedef sqlite3 Database;
typedef struct database_statement_t DatabaseStatement;
struct database_statement_t
{
    sqlite3_stmt *stmt;
    char *err;
};

Database *
db_open();

int
db_exec(Database *db, const char *sql, char **err);

DatabaseStatement
db_prepare(Database *db, const char *sql);

void
db_close(Database *db);

#endif

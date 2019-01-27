#ifndef _DB_H
#define _DB_H

#include <sqlite3.h>
#include <stdlib.h>

#define DB_FILEPATH "reg.db"

#define DB_ERR

typedef sqlite3 Database;
typedef struct database_statement_t DatabaseStatement;
struct database_statement_t
{
    sqlite3_stmt *stmt;
    char *err;
};

Database *
db_open();

DatabaseStatement
db_prepare(Database *db, const char *sql);

void
db_close(Database *db);

#endif

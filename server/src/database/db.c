#include "db.h"

Database *
db_open()
{
    sqlite3 *db;
    int rc;

    rc = sqlite3_open(DB_FILEPATH, &db);
    if (rc)
    {
        return NULL;
    }

    return db;
}

int
db_exec(Database *db, const char *sql, char **err)
{
    return sqlite3_exec(db, sql, NULL, NULL, err);
}

DatabaseStatement
db_prepare(Database *db, const char *sql)
{
    DatabaseStatement statement;
    statement.err = NULL;

    if (sqlite3_prepare_v2(db, sql, -1, &statement.stmt, NULL) != SQLITE_OK)
    {
        statement.err = (char *)sqlite3_errmsg(db);
    }

    return statement;
}

void
db_close(Database *db)
{
    while (sqlite3_close(db) == SQLITE_BUSY)
        ;
}

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

DatabaseStatement
db_prepare(Database *db, const char *sql)
{
    DatabaseStatement statement;
    statement.err = NULL;

    if (sqlite3_prepare(db, sql, -1, &statement.stmt, NULL) != SQLITE_OK)
    {
        statement.err = (char *)sqlite3_errmsg(db);
    }

    return statement;
}

void
db_close(Database *db)
{
    while (sqlite3_close(db) == SQLITE_BUSY);
}

#include "db.h"

/**
 *  Open a database stream
 */
Database *
db_open()
{
    sqlite3 *db;
    int rc;

    rc = sqlite3_open(CONFIG(CONFIG_DB_PATH, CONFIG_DB_PATH_DEFAULT), &db);
    if (rc)
    {
        return NULL;
    }

    return db;
}

/**
 *  Execute SQL query
 * 
 *  @param      db      the database object, returned from db_open (db.h)
 *  @param      sql     the sql query
 *  @param      err     a potential error
 */
int
db_exec(Database *db, const char *sql, char **err)
{
    return sqlite3_exec(db, sql, NULL, NULL, err);
}

/**
 *  Prepare an SQL query
 * 
 *  @param      db      the database object, returned from db_open (db.h)
 *  @param      sql     the sql query
 */
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

/**
 *  Prepare an SQL query
 * 
 *  @param      db      the database object, returned from db_open (db.h)
 */
void
db_close(Database *db)
{
    while (sqlite3_close(db) == SQLITE_BUSY)
        ;
}

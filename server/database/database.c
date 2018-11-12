#include "database.h"

int open(sqlite3 *db)
{
    sqlite3 *db;
    int code = 0;

    code = sqlite3_open_v2("db.sqlite", &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);

    return code;
}

#include "database.h"

sqlite3*
db_open()
{
    sqlite3 *db;
    int rc = sqlite3_open("reg.db", &db);

    if(rc) {
        return NULL;
    }

    return db;
}

void
db_close(sqlite3 *db)
{
    sqlite3_close(db);
}
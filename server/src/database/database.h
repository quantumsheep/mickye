#ifndef _DATABASE_H
#define _DATABASE_H

#include <sqlite3.h>
#include <stdlib.h>

sqlite3*
db_open();

void
db_close(sqlite3 *db);

#endif

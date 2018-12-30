#include <sqlite3.h>
#include <stdlib.h>

sqlite3*
db_open();

void
db_close(sqlite3 *db);
#ifndef _DB_INITIALIZER_H
#define _DB_INITIALIZER_H

#include "../file/file.h"
#include "../streams/console.h"
#include "db.h"
#include <stdio.h>
#include <unistd.h>

#define DB_SCRIPT_INIT_PATH "init.sql"

int
db_installed(Database *db);

void
db_init(Database *db);

#endif

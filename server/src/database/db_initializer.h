#ifndef _DB_INITIALIZER_H
#define _DB_INITIALIZER_H

#include <stdio.h>
#include <unistd.h>

#include "../config.h"
#include "../file/file.h"
#include "../streams/console.h"
#include "db.h"

#define CONFIG_DB_SCRIPT_PATH "db_script_path"
#define CONFIG_DB_SCRIPT_PATH_DEFAULT "static/init.sql"

int
db_installed(Database *db);

void
db_init(Database *db);

#endif

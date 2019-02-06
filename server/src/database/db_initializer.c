#include "db_initializer.h"

struct _defined_tables_t
{
    int log;
};

int
db_installed(Database *db)
{
    int rc;
    char *name;
    struct _defined_tables_t defined;
    defined.log = 0;

    DatabaseStatement statement;

    statement = db_prepare(db, "SELECT name FROM sqlite_master WHERE type='table';");

    while ((rc = sqlite3_step(statement.stmt)) == SQLITE_ROW)
    {
        name = (char *)sqlite3_column_text(statement.stmt, 0);

        if (strcmp(name, "log"))
            defined.log = 1;
    }

    return defined.log;
}

void
db_init(Database *db)
{
    char *query;
    char *err;

    if (!db_installed(db))
    {
        query = file_read(CONFIG(CONFIG_DB_SCRIPT_PATH, CONFIG_DB_SCRIPT_PATH_DEFAULT));

        if (query == NULL)
        {
            console_err("Database can't be initiated. (initialization script not found)\n");
            exit(1);
        }

        db_exec(db, query, &err);

        free(query);
    }
}
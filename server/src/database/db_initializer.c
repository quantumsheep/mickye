#include "db_initializer.h"

struct _defined_tables_t
{
    int log;
    int client;
};

int
db_installed(Database *db)
{
    int rc;
    char *name;
    struct _defined_tables_t defined;
    defined.log = 0;
    defined.client = 0;

    DatabaseStatement statement;

    statement = db_prepare(db, "SELECT name FROM sqlite_master WHERE type='table';");

    while ((rc = sqlite3_step(statement.stmt)) == SQLITE_ROW)
    {
        name = (char *)sqlite3_column_text(statement.stmt, 0);

        if (strcmp(name, "log"))
            defined.log = 1;
        else if (strcmp(name, "client"))
            defined.client = 1;
    }

    return defined.log && defined.client;
}

void
db_init(Database *db)
{
    char *query;
    char *err;

    if (!db_installed(db))
    {
        query = file_read(DB_SCRIPT_INIT_PATH);

        if (query == NULL)
        {
            console_err("Database can't be initiated. (initialization script not found)\n");
            exit(1);
        }

        db_exec(db, query, &err);

        free(query);
    }
}
#include "db_initializer.h"

int
db_installed(Database *db)
{
    // NOT IMPLEMENTED YET
    return 1;
}

void
db_init(Database *db)
{
    DatabaseStatement statement;

    char *query;

    if (!db_installed(db))
    {
        query = file_read(DB_SCRIPT_INIT_PATH);

        if (query == NULL)
        {
            console_err("Database can't be initiated (initialization script not found)\n");
            exit(1);
        }

        statement = db_prepare(db, query);
        sqlite3_step(statement.stmt);

        free(query);
    }
}
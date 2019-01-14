#include "client.h"

enum
{
    COL_NAME = 0,
    COL_STATUS,
    NUM_COLS
};

void
add_client(GtkListStore *store, char *ip_str, char *status)
{
    GtkTreeIter iter;

    gtk_list_store_insert_with_values(store, &iter, -1, COL_NAME, ip_str,
                                      COL_STATUS, status, -1);
}
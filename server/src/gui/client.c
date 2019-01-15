#include "client.h"

enum
{
    COL_NAME = 0,
    COL_STATUS,
    NUM_COLS
};

void
client_add(GtkListStore *store, char *ip_str, char *status)
{
    GtkTreeIter iter;

    gtk_list_store_insert_with_values(store, &iter, -1, COL_NAME, ip_str, COL_STATUS, status, -1);
}

void
client_connect(GtkWidget *connect_button, GtkBuilder *builder)
{
    // GtkWidget *tree = (GtkWidget*)data;

    // GtkTreeSelection *delected_client =
    //     gtk_tree_view_get_selection(GTK_TREE_VIEW(tree_view));
    gtk_widget_set_sensitive(connect_button, 0);
}
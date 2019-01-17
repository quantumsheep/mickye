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
client_connect(GtkWidget *connect_button, GtkBuilder *builder, GuiEnv *data)
{
    // GtkWidget *tree;
    // GtkTreeSelection *selected_client;
    // gpointer *test;

    // tree = (GtkWidget *)data;

    // selected_client =gtk_tree_view_get_selection(GTK_TREE_VIEW(tree));

    // test = gtk_tree_selection_get_user_data(selected_client);

    gtk_widget_set_sensitive(connect_button, 0);
    // log_add(data->text_view, "Trying to connect", "Client");
}
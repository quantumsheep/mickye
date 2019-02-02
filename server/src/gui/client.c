#include "client.h"

enum
{
    COL_NAME = 0,
    COL_STATUS,
    NUM_COLS
};

void
client_add(GtkListStore *store, char *ip_str, int status)
{
    GtkTreeIter iter;
    char *status_str;

    switch (status)
    {
    case CLIENT_CONNECTED:
        status_str = "Connected";
        break;
    case CLIENT_DISCONNECTED:
        status_str = "Disconnected";
        break;
    default:
        status_str = "Unknown";
        break;
    }

    gtk_list_store_insert_with_values(store, &iter, -1, COL_NAME, ip_str, COL_STATUS, status_str, -1);
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
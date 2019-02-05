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
    GtkTreeSelection *selection;
    GtkTreeIter iter;
    GValue value;
    GtkTreeModel *model;
    GtkTreeView *client_tree;
    char selected_ip[200];

    client_tree = GTK_TREE_VIEW(data->client_tree);
    model = GTK_TREE_MODEL(data->store);

    selection = gtk_tree_view_get_selection(client_tree);
    gtk_tree_selection_set_mode(selection, GTK_SELECTION_SINGLE);

    if (gtk_tree_selection_get_selected(selection, &model, &iter))
    {
        gtk_tree_model_get_value(model, &iter, 0, &value);

        strcpy(selected_ip, g_value_dup_string(&value));
        g_value_unset(&value);

        log_add(data->text_view, "Trying to connect to", selected_ip);

        call_terminal(selected_ip, 600, 300);
    }
    else
    {
        log_add(data->text_view, "Failed to connect", "Please select a connected client.");
    }
}
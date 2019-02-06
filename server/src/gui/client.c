#include "client.h"

enum
{
    COL_NAME = 0,
    COL_SOCKET,
    COL_IPV4,
    COL_STATUS,
    NUM_COLS
};

void
client_add(GtkListStore *store, TcpClient *client, int status)
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

    gtk_list_store_insert_with_values(store, &iter, -1, COL_NAME, "", COL_SOCKET, client->socket, COL_IPV4, client->ipv4, COL_STATUS, status_str, -1);
}

void
client_connect(GtkWidget *_, GtkBuilder *builder, GuiEnv *data)
{
    GtkTreeSelection *selection;
    GtkTreeIter iter;
    GValue value = G_VALUE_INIT;
    GtkTreeModel *model;
    GtkTreeView *client_tree;
    TcpClient *client;
    int client_id;

    client = NULL;
    client_id = -1;
    client_tree = GTK_TREE_VIEW(data->client_tree);
    model = gtk_tree_view_get_model(client_tree);

    selection = gtk_tree_view_get_selection(client_tree);
    gtk_tree_selection_set_mode(selection, GTK_SELECTION_SINGLE);

    if (gtk_tree_selection_get_selected(selection, &model, &iter))
    {
        gtk_tree_model_get_value(model, &iter, COL_SOCKET, &value);

        client_id = g_value_get_int(&value);
        g_value_unset(&value);

        if (client_id)
        {
            client = tcp_get_client(client_id);

            if (client != NULL)
            {
                log_add(data->text_view, "Trying to connect to", client->ipv4);

                call_terminal(client->ipv4, 600, 300);
            }
            else
            {
                log_add(data->text_view, "Failed to connect", "Can't get client informations.");
            }
        }
        else
        {
            log_add(data->text_view, "Failed to connect", "Can't get client ID.");
        }
    }
    else
    {
        log_add(data->text_view, "Failed to connect", "Please select a connected client.");
    }
}
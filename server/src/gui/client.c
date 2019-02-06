#include "client.h"

//Declaring collumns enumerator for the Store
enum
{
    COL_NAME = 0,
    COL_SOCKET,
    COL_IPV4,
    COL_STATUS,
    NUM_COLS
};

/*
*   Function to add client in the ListStore (GtkListStore) corresponding to the list of clients
*   Asking for :
*   @param      store      the main ListStore of the client list window
*   @param      client     a TcpClient object corresponding of a TcpClient struct
*   @param      status     a int corresponding to the status of the client (connected, disconnected...)
*/
void
client_add(GtkListStore *store, TcpClient *client, int status)
{
    GtkTreeIter iter;
    char *status_str;

    // status can correspond to a typedef status
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

    // inserting the new row with sets values
    gtk_list_store_insert_with_values(store, &iter, -1, COL_NAME, "", COL_SOCKET, client->socket, COL_IPV4, client->ipv4, COL_STATUS, status_str, -1);
}

/*
*   Function to connect with a client in the ListStore (GtkListStore) corresponding to the list of clients
*   Asking for :
*   @param      _      a unused widget (fault is going to gui_add_handler function...) can be NULL
*   @param      __     a unused builder (fault is going to gui_add_handler function...) can be NULL
*   @param      data   GuiEnv data set in main
*/
void
client_connect(GtkWidget *_, GtkBuilder *__, GuiEnv *data)
{
    GtkTreeSelection *selection;
    GtkTreeIter iter;
    GValue value = G_VALUE_INIT;
    GtkTreeModel *model;
    GtkTreeView *client_tree;
    TcpClient *client;
    int client_id;

    // Initialize variables, from data and client relative
    client = NULL;
    client_id = -1;
    client_tree = GTK_TREE_VIEW(data->client_tree);
    model = gtk_tree_view_get_model(client_tree);

    // Get the selected element of the treeView by the user
    selection = gtk_tree_view_get_selection(client_tree);
    gtk_tree_selection_set_mode(selection, GTK_SELECTION_SINGLE);

    // Set the iter to the selectionned item
    if (gtk_tree_selection_get_selected(selection, &model, &iter))
    {
        // Get the GValue of selected item
        gtk_tree_model_get_value(model, &iter, COL_SOCKET, &value);
        client_id = g_value_get_int(&value);
        g_value_unset(&value);

        // If client_id exist, create the client, if client != NULL try to connect, else for the two if, send a error log.
        if (client_id)
        {
            client = tcp_get_client(client_id);

            if (client != NULL)
            {
                log_add(data->text_view, "Trying to connect to", client->ipv4);

                terminal_start(client, data);
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
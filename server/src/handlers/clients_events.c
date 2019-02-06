#include "clients_events.h"

GtkTextView *text_view;
GtkWidget *entry;
GtkWindow *rename_window;
int client_id;

/*
*   Function to connect to a client after clicking one the "connect" options of the menu
*   
*   @param      _      the unused widget for the menu option
*   @param      data   GuiEnv data set in main
*/
void
popup_connect(GtkWidget *_, GuiEnv *data)
{
    client_connect(NULL, NULL, data);
}

void
rename_client_from_iter(GtkTreeModel *model, GtkTreeIter iter, GValue value, GuiEnv *data, char *name)
{
    char *ipv4;
    char *status;
    int socket;

    gtk_tree_model_get_value(model, &iter, COL_SOCKET, &value);
    socket = g_value_get_int(&value);
    g_value_unset(&value);
    gtk_tree_model_get_value(model, &iter, COL_IPV4, &value);
    ipv4 = g_value_dup_string(&value);
    g_value_unset(&value);
    gtk_tree_model_get_value(model, &iter, COL_STATUS, &value);
    status = g_value_dup_string(&value);
    g_value_unset(&value);

    gtk_list_store_remove((GtkListStore *)data->store, &iter);
    gtk_list_store_insert_with_values(data->store, &iter, -1, COL_NAME, name, COL_SOCKET, socket, COL_IPV4, ipv4, COL_STATUS, status, -1);
}

/*
*   Function to rename a client after clicking one the "rename" options of the menu
*   
*   @param      entry       the widget for the entry who have the entered text
*   @param      data        GuiEnv data set in main
*/
void
rename_client(GtkWidget *entry, GuiEnv *data)
{
    GtkEntryBuffer *Entrybuffer;
    GtkTreeIter iter;
    GtkTreeModel *model;
    GtkTreeView *client_tree;
    GValue value = G_VALUE_INIT;
    char *name;
    int validate;

    // Initialize client_tree, model, the buffer of the entry, the new asked name of all the widgets in popup rename window
    client_tree = GTK_TREE_VIEW(data->client_tree);
    model = gtk_tree_view_get_model(client_tree);
    Entrybuffer = gtk_entry_get_buffer(GTK_ENTRY(entry));
    name = (char *)gtk_entry_buffer_get_text(Entrybuffer);

    if (gtk_tree_model_get_iter_first(model, &iter))
    {
        gtk_tree_model_get_value(model, &iter, COL_SOCKET, &value);
        validate = g_value_get_int(&value);
        g_value_unset(&value);
        if (validate == client_id)
        {
            rename_client_from_iter(model, iter, value, data, name);
        }
        else
        {
            if (gtk_tree_model_iter_next(model, &iter))
            {
                gtk_tree_model_get_value(model, &iter, COL_SOCKET, &value);
                validate = g_value_get_int(&value);
                g_value_unset(&value);
                if (validate == client_id)
                {
                    rename_client_from_iter(model, iter, value, data, name);
                }
            }
        }
    }

    // Remove the entry text after ENTER, destroy the entry and the rename popup window
    gtk_entry_buffer_delete_text(Entrybuffer, 0, strlen(name));
    gtk_widget_destroy(entry);
    gtk_window_close(GTK_WINDOW(rename_window));
}

/*
*   Function to create the popup rename event
*   
*   @param      _      the unused widget for the rename popup window
*   @param      data   GuiEnv data set in main
*/
void
popup_rename(GtkWidget *_, GuiEnv *data)
{
    GtkTreeSelection *selection;
    GtkTreeIter iter;
    GtkTreeModel *model;
    GValue value = G_VALUE_INIT;

    //Getting the selected client of the client list
    selection = gtk_tree_view_get_selection((GtkTreeView *)data->client_tree);
    gtk_tree_selection_set_mode(selection, GTK_SELECTION_SINGLE);

    //If a client is selected, get the socket value, get the ipv4 value, get the status of the client, remove it and recreate it with the new asked name
    if (gtk_tree_selection_get_selected(selection, &model, &iter))
    {
        gtk_tree_model_get_value(model, &iter, COL_SOCKET, &value);
        client_id = g_value_get_int(&value);
        g_value_unset(&value);
    }

    // Create the popup rename popup window
    rename_window = (GtkWindow *)gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(rename_window, "Rename");
    gtk_window_set_default_size(rename_window, 200, 0);
    gtk_window_set_position(rename_window, GTK_WIN_POS_MOUSE);
    gtk_window_set_resizable(rename_window, FALSE);

    // Create the entry of the rename popup window
    entry = gtk_entry_new();
    g_signal_connect(entry, "activate", (GCallback)rename_client, data);

    //Add the entry to the rename popup window
    gtk_container_add((GtkContainer *)rename_window, entry);

    // Show the rename popup window
    gtk_widget_show_all(GTK_WIDGET(rename_window));
}

/*
*   Function to delete a client after clicking one the "delete" options of the menu
*   
*   @param      _      the unused widget for the menu option
*   @param      data   GuiEnv data set in main
*/
void
delete_client(GtkWidget *_, GuiEnv *data)
{
    GtkTreeSelection *selection;
    GtkTreeIter iter;
    GtkTreeModel *model;
    GtkTreeView *client_tree;
    GValue value = G_VALUE_INIT;
    int client_id;

    // Initialize the client_tree and the model from data
    client_tree = GTK_TREE_VIEW(data->client_tree);
    model = gtk_tree_view_get_model(client_tree);

    // Get the selected client of the client list
    selection = gtk_tree_view_get_selection(client_tree);
    gtk_tree_selection_set_mode(selection, GTK_SELECTION_SINGLE);

    // If a client is selected, remove it and close the socket connection
    if (gtk_tree_selection_get_selected(selection, &model, &iter))
    {
        // Get the socket adress and close it
        gtk_tree_model_get_value(model, &iter, COL_SOCKET, &value);
        client_id = g_value_get_int(&value);
        g_value_unset(&value);
        tcp_annihilate_socket(client_id);

        // Remove the client from the list
        gtk_list_store_remove((GtkListStore *)data->store, &iter);
    }
}

/*
*   Function to create the menu list on right click
*   
*   @param      data    GuiEnv data set in main
*   @param      event   the event catched from the user click
*/
void
show_popmenu(GuiEnv *data, GdkEventButton *event)
{
    GtkWidget *menu;
    GtkWidget *menu_connect_item;
    GtkWidget *menu_rename_item;
    GtkWidget *menu_delete_item;

    // Create the menu and adding the items
    menu = gtk_menu_new();
    menu_connect_item = gtk_menu_item_new_with_label("Connect to the selected client.");
    menu_rename_item = gtk_menu_item_new_with_label("Rename selected client.");
    menu_delete_item = gtk_menu_item_new_with_label("Remove selected client");

    // Adding all the events for each menu items
    g_signal_connect(menu_connect_item, "activate", (GCallback)popup_connect, data);
    g_signal_connect(menu_rename_item, "activate", (GCallback)popup_rename, data);
    g_signal_connect(menu_delete_item, "activate", (GCallback)delete_client, data);

    // Append all the items to the menu
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), menu_connect_item);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), menu_rename_item);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), menu_delete_item);

    // Show the menu (and the childs items)
    gtk_widget_show_all(menu);

    // Make the menu appear on the mouse
    gtk_menu_popup_at_pointer(GTK_MENU(menu), (GdkEvent *)event);
}

/*
*   Boolean function to catch the click of the user
*   
*   @param      _           the unused widget for the tree_view
*   @param      event       the event type of the click (right click or not ?)
*   @param      data        GuiEnv data set in main
*/
gboolean
trigger_clients_button_press(GtkWidget *_, GdkEventButton *event, GuiEnv *data)
{
    // If the event is a right click, show the popup and trigger the event
    if (event->type == GDK_BUTTON_PRESS && event->button == 3)
    {
        show_popmenu(data, event);
        return TRUE;
    }
    return FALSE;
}

/*
*   Function to catch the popup_menu event
*   
*   @param      _      the unused widget for the tree_view
*   @param      data   GuiEnv data set in main
*/
gboolean
on_popup(GtkWidget *_, GuiEnv *data)
{
    // Ask to show the menu and send it a NULL event
    show_popmenu(data, NULL);
    return TRUE;
}

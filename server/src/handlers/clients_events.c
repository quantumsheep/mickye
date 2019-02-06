
#include "clients_events.h"

GtkTextView *text_view;
GtkWidget *entry;
GtkWindow *rename_window;

void
popup_connect(GtkWidget *menu_connect_item, GuiEnv *data)
{
    client_connect(NULL, NULL, data);
}

void
rename_client(GtkWidget *entry, GuiEnv *data)
{
    GtkEntryBuffer *Entrybuffer;
    GtkTreeSelection *selection;
    GtkTreeIter iter;
    GtkTreeModel *model;
    GtkTreeView *client_tree;
    GValue value = G_VALUE_INIT;
    char *name;
    char *ipv4;
    char *status;
    int socket;

    client_tree = GTK_TREE_VIEW(data->client_tree);
    model = gtk_tree_view_get_model(client_tree);

    Entrybuffer = gtk_entry_get_buffer(GTK_ENTRY(entry));
    name = (char *)gtk_entry_buffer_get_text(Entrybuffer);

    selection = gtk_tree_view_get_selection(client_tree);
    gtk_tree_selection_set_mode(selection, GTK_SELECTION_SINGLE);

    if (gtk_tree_selection_get_selected(selection, &model, &iter))
    {
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

    gtk_entry_buffer_delete_text(Entrybuffer, 0, strlen(name));
    gtk_widget_destroy(entry);
    gtk_window_close(GTK_WINDOW(rename_window));
}

void
popup_rename(GtkWidget *menuitem, GuiEnv *data)
{
    rename_window = (GtkWindow *)gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(rename_window, "Rename");
    gtk_window_set_default_size(rename_window, 200, 0);
    gtk_window_set_position(rename_window, GTK_WIN_POS_MOUSE);
    gtk_window_set_resizable(rename_window, FALSE);

    entry = gtk_entry_new();
    g_signal_connect(entry, "activate", (GCallback)rename_client, data);

    gtk_container_add((GtkContainer *)rename_window, entry);

    gtk_widget_show_all(GTK_WIDGET(rename_window));
}

void
delete_client(GtkWidget *menuitem, GuiEnv *data)
{
    GtkTreeSelection *selection;
    GtkTreeIter iter;
    GtkTreeModel *model;
    GtkTreeView *client_tree;
    GValue value = G_VALUE_INIT;
    int client_id;

    client_tree = GTK_TREE_VIEW(data->client_tree);
    model = gtk_tree_view_get_model(client_tree);

    selection = gtk_tree_view_get_selection(client_tree);
    gtk_tree_selection_set_mode(selection, GTK_SELECTION_SINGLE);

    if (gtk_tree_selection_get_selected(selection, &model, &iter))
    {
        gtk_tree_model_get_value(model, &iter, COL_SOCKET, &value);
        client_id = g_value_get_int(&value);
        g_value_unset(&value);

        tcp_annihilate_socket(client_id);
        gtk_list_store_remove((GtkListStore *)data->store, &iter);
    }
}

void
show_popmenu(GuiEnv *data, GdkEventButton *event)
{
    GtkWidget *menu;
    GtkWidget *menu_connect_item;
    GtkWidget *menu_rename_item;
    GtkWidget *menu_delete_item;

    menu = gtk_menu_new();
    menu_connect_item = gtk_menu_item_new_with_label("Connect to the selected client.");
    menu_rename_item = gtk_menu_item_new_with_label("Rename selected client.");
    menu_delete_item = gtk_menu_item_new_with_label("Remove selected client");

    g_signal_connect(menu_connect_item, "activate", (GCallback)popup_connect, data);
    g_signal_connect(menu_rename_item, "activate", (GCallback)popup_rename, data);
    g_signal_connect(menu_delete_item, "activate", (GCallback)delete_client, data);

    gtk_menu_shell_append(GTK_MENU_SHELL(menu), menu_connect_item);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), menu_rename_item);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), menu_delete_item);

    gtk_widget_show_all(menu);

    gtk_menu_popup_at_pointer(GTK_MENU(menu), (GdkEvent *)event);
}

gboolean
trigger_clients_button_press(GtkWidget *tree_view, GdkEventButton *event, GuiEnv *data)
{
    if (event->type == GDK_BUTTON_PRESS && event->button == 3)
    {
        show_popmenu(data, event);
        return TRUE;
    }
    return FALSE;
}

gboolean
on_popup(GtkWidget *tree_view, GuiEnv *data)
{
    show_popmenu(data, NULL);
    return TRUE;
}

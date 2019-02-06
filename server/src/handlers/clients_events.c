
#include "clients_events.h"

GtkTextView *text_view;
GtkWidget *entry;

void
popup_connect(GtkWidget *menu_connect_item, GuiEnv *data)
{
    client_connect(NULL, NULL, data);
}

void
rename_client(GtkWidget *entry, GuiEnv *data)
{
    GtkEntryBuffer *Entrybuffer;
    char *text;
    GtkTreeSelection *selection;
    GtkTreeIter iter;
    GValue new_name = G_VALUE_INIT;
    GtkTreeModel *model;
    GtkTreeView *client_tree;

    client_tree = GTK_TREE_VIEW(data->client_tree);
    model = gtk_tree_view_get_model(client_tree);

    Entrybuffer = gtk_entry_get_buffer(GTK_ENTRY(entry));
    text = (char *)gtk_entry_buffer_get_text(Entrybuffer);
    g_value_init(&new_name, G_TYPE_STRING);
    g_value_set_static_string(&new_name, text);

    selection = gtk_tree_view_get_selection(client_tree);
    gtk_tree_selection_set_mode(selection, GTK_SELECTION_SINGLE);

    if (gtk_tree_selection_get_selected(selection, &model, &iter))
    {
        gtk_tree_store_set((GtkTreeStore *)data->store, &iter, 2, "Foo", -1);
    }

    gtk_entry_buffer_delete_text(Entrybuffer, 0, strlen(text));
}

void
popup_rename(GtkWidget *menuitem, GuiEnv *data)
{
    GtkWindow *rename_window;

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

    client_tree = GTK_TREE_VIEW(data->client_tree);
    model = gtk_tree_view_get_model(client_tree);

    selection = gtk_tree_view_get_selection(client_tree);
    gtk_tree_selection_set_mode(selection, GTK_SELECTION_SINGLE);

    if (gtk_tree_selection_get_selected(selection, &model, &iter))
    {
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

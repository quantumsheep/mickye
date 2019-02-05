
#include "clients_events.h"

GtkTextView *text_view;

void
popup_connect(GtkWidget *menuitem, gpointer userdata)
{
    GuiEnv gui_env;
    GtkTreeView *tree_view;

    tree_view = GTK_TREE_VIEW(userdata);

    gui_env.client_tree = (GtkWidget *)tree_view;
    gui_env.store = gtk_tree_view_get_model(gui_env.client_tree);
    gui_env.text_view = text_view;

    client_connect(NULL, NULL, &gui_env);
}

void
popup_rename(GtkWidget *menuitem)
{
    GtkWidget *entry;
    GtkWindow *rename_window;

    rename_window = (GtkWindow *)gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(rename_window, "Rename");
    gtk_window_set_default_size(rename_window, 200, 0);

    entry = gtk_entry_new();
    // g_signal_connect(entry, "activate", printf("\noui"), NULL);
    gtk_container_add(rename_window, entry);

    gtk_widget_show_all(GTK_WIDGET(rename_window));
}

void
show_popmenu(GtkWidget *tree_view, GdkEventButton *event)
{
    GtkWidget *menu;
    GtkWidget *menu_connect_item;
    GtkWidget *menu_rename_item;

    menu = gtk_menu_new();
    menu_connect_item = gtk_menu_item_new_with_label("Connect to the selected client.");
    menu_rename_item = gtk_menu_item_new_with_label("Rename the client.");

    g_signal_connect(menu_connect_item, "activate", (GCallback)popup_connect, tree_view);
    g_signal_connect(menu_rename_item, "activate", (GCallback)popup_rename, NULL);

    gtk_menu_shell_append(GTK_MENU_SHELL(menu), menu_connect_item);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), menu_rename_item);

    gtk_widget_show_all(menu);
    gtk_menu_popup(GTK_MENU(menu), NULL, NULL, NULL, NULL, (event != NULL) ? event->button : 0, gdk_event_get_time((GdkEvent *)event));
}

gboolean
trigger_clients_button_press(GtkWidget *tree_view, GdkEventButton *event,  GtkTextView *main_text_view)
{
    text_view = main_text_view;
    if (event->type == GDK_BUTTON_PRESS && event->button == 3)
    {
        show_popmenu(tree_view, event);
        return TRUE;
    }
    return FALSE;
}

gboolean
on_popup(GtkWidget *tree_view, GtkTextView *main_text_view)
{
    text_view = main_text_view;
    show_popmenu(tree_view, NULL);
    return TRUE;
}


#include "clients_events.h"

GtkWidget *treeview;

void
popup_connect(GtkWidget *menuitem, gpointer userdata)
{
    GtkTreeView *treeview = GTK_TREE_VIEW(userdata);
    g_print ("Do something!\n");
}

void
show_popmenu(GtkWidget *treeview, GdkEventButton *event, gpointer userdata)
{
    GtkWidget *menu;
    GtkWidget *menuitem;

    menu = gtk_menu_new();
    menuitem = gtk_menu_item_new_with_label("Connect to the selected client.");

    g_signal_connect(menuitem, "activate", (GCallback)popup_connect, NULL);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), menuitem);
    gtk_widget_show_all(menu);
    gtk_menu_popup(GTK_MENU(menu), NULL, NULL, NULL, NULL, (event != NULL) ? event->button : 0, gdk_event_get_time((GdkEvent *)event));
}

gboolean
trigger_clients_button_press(GtkWidget *widget, GdkEventButton *event, gpointer userdata)
{
    treeview = widget;

    if (event->type == GDK_BUTTON_PRESS && event->button == 3)
    {
        show_popmenu(treeview, event, userdata);
        return TRUE;
    }
    return FALSE;
}

gboolean
on_popup(GtkWidget *widget, gpointer userdata)
{
    treeview = widget;

    show_popmenu(treeview, NULL, userdata);
    return TRUE;
}

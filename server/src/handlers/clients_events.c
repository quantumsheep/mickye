#include "clients_events.h"

void
view_popup_menu(GtkWidget *treeview, GdkEventButton *event, gpointer userdata)
{
    GtkWidget *menu, *menuitem;

    menu = gtk_menu_new();
    menuitem = gtk_menu_item_new_with_label("Do something");

    gui_add_handler(menuitem, "activate", "clicked", client_connect, &gui_env);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), menuitem);

    gtk_widget_show_all(menu);
    gtk_menu_popup(GTK_MENU(menu), NULL, NULL, NULL, NULL,
                   (event != NULL) ? event->button : 0,
                   gdk_event_get_time((GdkEvent *)event));
}

gboolean
clients_events_trigger(GtkWidget *widget, GtkBuilder *builder, GdkEventButton *ev, GuiEnv *data)
{
    view_popup_menu(treeview, NULL, userdata);

    return TRUE;
}
#include "clients_events.h"

void
clients_events_trigger(GtkWidget *widget, GtkBuilder *builder, GdkEventButton *ev, GuiEnv *data)
{
    GtkWidget *menu, *menuitem;

    menu = gtk_menu_new();
    menuitem = gtk_menu_item_new_with_label("Connect");

    g_signal_connect(menuitem, "activate", (GCallback)client_connect, widget);

    gtk_menu_shell_append(GTK_MENU_SHELL(menu), menuitem);

    gtk_widget_show_all(menu);
    gtk_menu_popup(GTK_MENU(menu), NULL, NULL, NULL, NULL,
                   (ev != NULL) ? ev->button : 0,
                   gdk_event_get_time((GdkEvent *)ev));
}
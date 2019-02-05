#include "clients_events.h"

gboolean
clients_events_trigger(GtkWidget *widget, GtkBuilder *builder, GdkEventButton *ev, GuiEnv *data)
{
    puts("OUI");

    return TRUE;
}
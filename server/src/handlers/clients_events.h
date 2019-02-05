#ifndef _HANDLERS_CLIENTS_EVENTS_H
#define _HANDLERS_CLIENTS_EVENTS_H

#include <gtk/gtk.h>
#include <stdio.h>

#include "../gui/env.h"
#include "../gui/client.h"
#include "../gui/builder.h"

void
clients_events_trigger(GtkWidget *widget, GtkBuilder *builder, GdkEventButton *ev, GuiEnv *data);

#endif

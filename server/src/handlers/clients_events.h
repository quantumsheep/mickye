#ifndef _HANDLERS_CLIENTS_EVENTS_H
#define _HANDLERS_CLIENTS_EVENTS_H

#include <gtk/gtk.h>
#include <stdio.h>

#include "../gui/builder.h"
#include "../gui/client.h"
#include "../gui/env.h"
#include "../gui/loader.h"

gboolean
trigger_clients_button_press(GtkWidget *tree_view, GdkEventButton *event, GuiEnv *data);

gboolean
on_popup(GtkWidget *tree_view, GuiEnv *data);

#endif

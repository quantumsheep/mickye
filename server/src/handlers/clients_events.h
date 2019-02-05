#ifndef _HANDLERS_CLIENTS_EVENTS_H
#define _HANDLERS_CLIENTS_EVENTS_H

#include <gtk/gtk.h>
#include <stdio.h>

#include "../gui/builder.h"
#include "../gui/client.h"
#include "../gui/env.h"

gboolean
trigger_clients_button_press(GtkWidget *widget, GdkEventButton *event, GtkTextView *text_view);

gboolean
on_popup(GtkWidget *widget, GtkTextView *text_view);

#endif

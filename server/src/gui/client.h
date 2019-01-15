#ifndef _GUI_CLIENT_H
#define _GUI_CLIENT_H

#include <gtk/gtk.h>

#include "env.h"

void
client_add(GtkListStore *store, char *ip_str, char *status);

void
client_connect(GtkWidget *connect_button, GtkBuilder *builder, GuiEnv *data);

#endif

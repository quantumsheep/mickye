#ifndef _GUI_CLIENT_H
#define _GUI_CLIENT_H

#include <gtk/gtk.h>

#include "log.h"
#include "env.h"

enum {
    CLIENT_CONNECTED = 1,
    CLIENT_DISCONNECTED
};

void
client_add(GtkListStore *store, char *ip_str, int status);

void
client_connect(GtkWidget *connect_button, GtkBuilder *builder, GuiEnv *data);

#endif

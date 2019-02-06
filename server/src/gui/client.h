#ifndef _GUI_CLIENT_H
#define _GUI_CLIENT_H

#include <gtk/gtk.h>

#include "../handlers/tcp.h"
#include "../handlers/tcp_client.h"
#include "env.h"
#include "log.h"
#include "terminal.h"

enum
{
    CLIENT_CONNECTED = 1,
    CLIENT_DISCONNECTED
};

gboolean
client_set_disconnect(int id, GuiEnv *data);

void
client_add(GtkListStore *store, TcpClient *client, int status);

void
client_connect(GtkWidget *connect_button, GtkBuilder *builder, GuiEnv *data);

#endif

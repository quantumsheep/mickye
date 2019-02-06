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

enum
{
    COL_NAME = 0,
    COL_SOCKET,
    COL_IPV4,
    COL_STATUS,
    NUM_COLS
};

void
client_add(GtkListStore *store, TcpClient *client, int status);

void
client_connect(GtkWidget *connect_button, GtkBuilder *builder, GuiEnv *data);

#endif

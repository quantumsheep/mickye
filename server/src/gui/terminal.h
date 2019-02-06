#ifndef _GUI_TERMINAL_H
#define _GUI_TERMINAL_H

#include <errno.h>
#include <gtk/gtk.h>
#include <pthread.h>
#include <string.h>
#include <sys/socket.h>
#include <vte/vte.h>

#include "../handlers/tcp.h"
#include "../handlers/tcp_client.h"

#define TERMINAL_DEFAULT_WIDTH 600
#define TERMINAL_DEFAULT_HEIGH 300

void
terminal_start(TcpClient *client, GuiEnv *env);

#endif

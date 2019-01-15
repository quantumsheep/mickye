#ifndef _HANDLERS_TCP_H
#define _HANDLERS_TCP_H

#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <gtk/gtk.h>

#include "../gui/env.h"
#include "../gui/builder.h"

void
start_server(GtkWidget *widget, GtkBuilder *builder, GuiEnv *data);

#endif

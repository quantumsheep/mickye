#ifndef _HANDLERS_TCP_H
#define _HANDLERS_TCP_H

#include <arpa/inet.h>
#include <gtk/gtk.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "../gui/builder.h"
#include "../gui/client.h"
#include "../gui/env.h"
#include "../gui/log.h"
#include "tcp_client.h"

#define TCP_SERVER_PORT 3000
#define TCP_SERVER_HOST "127.0.0.1"

#define TCP_CHUNK_SIZE 8192

TcpClient *
tcp_get_client(int id);

void
tcp_annihilate_socket(int socket);

void
start_server(GtkWidget *widget, GtkBuilder *builder, GuiEnv *data);

void
stop_server(GtkWidget *widget, GtkBuilder *builder, GuiEnv *data);

#endif

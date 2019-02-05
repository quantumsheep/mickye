#ifndef _HANDLERS_TCP_H
#define _HANDLERS_TCP_H

#include <arpa/inet.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <gtk/gtk.h>

#include "../gui/env.h"
#include "../gui/builder.h"
#include "../gui/log.h"
#include "../gui/client.h"

#define TCP_SERVER_PORT 3000
#define TCP_SERVER_HOST "127.0.0.1"

#define TCP_CHUNK_SIZE 8192

typedef struct tcp_client_t TcpClient;
struct tcp_client_t
{
    int socket;
    char ipv4[INET_ADDRSTRLEN];
    char ipv6[INET6_ADDRSTRLEN];
};

void
tcp_annihilate_socket(int socket);

void
start_server(GtkWidget *widget, GtkBuilder *builder, GuiEnv *data);

void
stop_server(GtkWidget *widget, GtkBuilder *builder, GuiEnv *data);

#endif

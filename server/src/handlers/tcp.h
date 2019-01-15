#ifndef _HANDLERS_TCP_H
#define _HANDLERS_TCP_H

#include "../gui/gui.h"

#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

void
start_server(GtkWidget *widget, GtkBuilder *builder);

#endif

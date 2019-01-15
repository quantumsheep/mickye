#ifndef _HANDLERS_TCP_H
#define _HANDLERS_TCP_H

#include "../gui/gui.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>

void
start_server(GtkWidget *widget, GtkBuilder* builder);

#endif

#ifndef _GUI_LOADER_H
#define _GUI_LOADER_H

#include <gtk/gtk.h>
#include <vte/vte.h>

#include "client.h"
#include "log.h"

void
load_clients_list(GtkBuilder *builder, GtkListStore *store, GtkWidget *client_tree);

void
load_terminal(GtkBuilder *builder);

void
load_logs(GtkBuilder *builder, GtkTextView *text_view);

void
load_interface(GtkBuilder *builder, GtkTextView *text_view, GtkListStore *store, GtkWidget *client_tree);
#endif

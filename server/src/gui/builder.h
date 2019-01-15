#ifndef _GUI_BUILDER_H
#define _GUI_BUILDER_H

#include <gtk/gtk.h>
#include <stdlib.h>

#define BUILDER_PATH "builder.ui"

void
gui_add_handler(GtkBuilder *builder, char *id, char *on, void *callback);

GtkBuilder*
gui_open_builder();

#endif

#ifndef _GUI_BUILDER_H
#define _GUI_BUILDER_H

#include <gtk/gtk.h>
#include <stdlib.h>

#include "env.h"

#define BUILDER_PATH "static/builder.ui"

void
gui_add_handler(GtkBuilder *builder, char *id, char *on, void (*callback), GuiEnv *data);

GtkBuilder *
gui_open_builder();

#endif

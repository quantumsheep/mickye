#ifndef _GUI_BUILDER_H
#define _GUI_BUILDER_H

#include <gtk/gtk.h>
#include <stdlib.h>

#include "env.h"
#include "../config.h"

#define CONFIG_BUILDER_PATH "gui_builder_path"
#define CONFIG_BUILDER_PATH_DEFAULT "static/builder.ui"

void
gui_add_handler(GtkBuilder *builder, char *id, char *on, void (*callback), GuiEnv *data);

GtkBuilder *
gui_open_builder();

#endif

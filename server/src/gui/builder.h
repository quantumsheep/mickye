#include <gtk/gtk.h>

#define BUILDER_PATH "builder.ui"

void
gui_add_handler(GtkBuilder *builder, char *id, char *on, void *callback);

GtkBuilder*
gui_open_builder();
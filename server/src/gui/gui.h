#include <gtk/gtk.h>

#define BUILDER_PATH "builder.ui"

void
add_handler(GtkBuilder *builder, char *id, char *on, void *callback);

GtkBuilder*
open_builder();

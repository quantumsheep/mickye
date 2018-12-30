#include <gtk/gtk.h>

#define BUILDER_PATH "builder.ui"

void
add_handler(GtkBuilder *builder, char *id, char *on, void *callback);

void
call_terminal();

void
error_modal();

void
create_window(gchar* title, gint width, gint height);

GtkBuilder*
open_builder();

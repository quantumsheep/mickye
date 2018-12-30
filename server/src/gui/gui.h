#include <gtk/gtk.h>

#define BUILDER_PATH "builder.ui"

void
gui_add_handler(GtkBuilder *builder, char *id, char *on, void *callback);

void
call_terminal();

void
error_modal();

void
create_window(gchar* title, gint width, gint height);

GtkBuilder*
gui_open_builder();

#include "gui.h"

static void
start_server(GtkWidget *widget, gpointer data)
{
  g_print("Hello World\n");
}

void add_handler(GtkBuilder *builder, char *id, char *on, void *callback) {
  GObject *obj = gtk_builder_get_object(builder, id);

  if(obj != NULL) {
    g_signal_connect(obj, on, G_CALLBACK(callback), NULL);
  }
}

GtkBuilder* open_builder() {
  GtkBuilder* builder = gtk_builder_new();
  GError *error = NULL;
  
  if (gtk_builder_add_from_file(builder, BUILDER_PATH, &error) == 0)
  {
      g_printerr("Error loading file: %s\n", error->message);
      g_clear_error(&error);

      return NULL;
  }

  return builder;
}
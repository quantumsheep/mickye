#include "gui.h"

void
add_handler(GtkBuilder *builder, char *id, char *on, void *callback)
{
    GObject *obj = gtk_builder_get_object(builder, id);

    if (obj != NULL) {
        g_signal_connect(obj, on, G_CALLBACK(callback), NULL);
    }
}

void
create_window(gchar* title, gint width, gint height){
    GtkWidget
    *terminal_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

    gtk_window_set_title (terminal_window,
                          title);

    gtk_window_set_default_size (terminal_window,
                             width,
                             height);

    gtk_widget_show (terminal_window);
}

void
error_modal()
{
    GtkWidget *
    dialog = gtk_dialog_new ();
    GtkWidget *
    close_button = gtk_dialog_add_button (GTK_DIALOG (dialog),
                                   "Close",
                                   GTK_RESPONSE_OK);

    int result = gtk_dialog_run (GTK_DIALOG (dialog));
    switch (result)
    {
        case GTK_RESPONSE_ACCEPT:
        // do_application_specific_something ();
        break;
        default:
        // do_nothing_since_dialog_was_cancelled ();
        break;
    }
    gtk_widget_destroy (dialog);
}

void
call_terminal()
{
    create_window("Terminal", 800, 600);
}

GtkBuilder*
open_builder()
{
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
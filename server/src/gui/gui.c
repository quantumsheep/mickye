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

    // GtkWidget
    // *image = gtk_image_new_from_file ("/home/mickdec/Bureau/mickey/server/src/gui/001.jpg");
    // gtk_container_add (GTK_CONTAINER (terminal_window), image);

    gtk_widget_show (terminal_window);
    // gtk_widget_show (image);
}

void
error_modal(gchar *error_message)
{
    GtkWidget
    *modal_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

    GtkWidget
    *dialog;

    GtkDialogFlags
    flags = GTK_DIALOG_DESTROY_WITH_PARENT;

    dialog = gtk_message_dialog_new (modal_window,
                                    flags,
                                    GTK_MESSAGE_ERROR,
                                    GTK_BUTTONS_CLOSE,
                                    error_message);

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
    error_modal("Ceci est un message d'erreur");
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
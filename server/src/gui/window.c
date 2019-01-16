#include "window.h"

void
create_window(char *title, int width, int height)
{
    GtkWindow *terminal_window =
        (GtkWindow *)gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_set_title(terminal_window, title);

    gtk_window_set_default_size(terminal_window, width, height);

    // GtkWidget
    // *image = gtk_image_new_from_file
    // ("/home/mickdec/Bureau/mickey/server/src/gui/001.jpg"); gtk_container_add
    // (GTK_CONTAINER (terminal_window), image);

    gtk_widget_show((GtkWidget *)terminal_window);
    // gtk_widget_show (image);
}

void
error_modal(char *error_message)
{
    GtkWindow *modal_window = (GtkWindow *)gtk_window_new(GTK_WINDOW_TOPLEVEL);

    GtkWidget *dialog = gtk_message_dialog_new(
        modal_window, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR,
        GTK_BUTTONS_CLOSE, error_message);

    int result = gtk_dialog_run(GTK_DIALOG(dialog));
    switch (result)
    {
    case GTK_RESPONSE_ACCEPT:
        // do_application_specific_something ();
        break;
    default:
        // do_nothing_since_dialog_was_cancelled ();
        break;
    }

    gtk_widget_destroy(dialog);
}

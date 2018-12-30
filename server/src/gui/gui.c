#include "gui.h"
#include <stdlib.h>

typedef struct gui_callback_params_t GUICallbackParams;
struct gui_callback_params_t
{
    void (*f)(GtkWidget*, GtkBuilder*);
    GtkBuilder* builder;
};

static void
_gui_caller(GtkWidget* widget, gpointer data)
{
    GUICallbackParams* params = data;
    params->f(widget, params->builder);
}

void
gui_add_handler(GtkBuilder *builder, char *id, char *on, void *callback)
{
    GUICallbackParams* params = (GUICallbackParams*)malloc(sizeof(GUICallbackParams));
    params->builder = builder;
    params->f = callback;

    GObject *obj = gtk_builder_get_object(builder, id);

    if (obj != NULL) 
        g_signal_connect(obj, on, G_CALLBACK(_gui_caller), params);
}

void
create_window(char* title, int width, int height){
    GtkWindow
    *terminal_window = (GtkWindow*)gtk_window_new (GTK_WINDOW_TOPLEVEL);

    gtk_window_set_title (terminal_window,
                          title);

    gtk_window_set_default_size (terminal_window,
                             width,
                             height);

    // GtkWidget
    // *image = gtk_image_new_from_file ("/home/mickdec/Bureau/mickey/server/src/gui/001.jpg");
    // gtk_container_add (GTK_CONTAINER (terminal_window), image);

    gtk_widget_show ((GtkWidget*)terminal_window);
    // gtk_widget_show (image);
}

void
error_modal(char *error_message)
{
    GtkWindow
    *modal_window = (GtkWindow*)gtk_window_new (GTK_WINDOW_TOPLEVEL);

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
gui_open_builder()
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
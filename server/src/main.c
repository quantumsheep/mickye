#include "gui/builder.h"
#include "gui/client.h"
#include "gui/loader.h"
#include "handlers/tcp.h"
#include <gtk/gtk.h>

int
main(int argc, char **argv)
{
    GuiEnv gui_env;

    GtkBuilder *builder;
    GtkTextView *text_view;
    GtkListStore *store;

    gtk_init(&argc, &argv);

    /**
     * Construct a GtkBuilder instance and load our UI description
     *
     * The builder.ui file can be edited before launching the software
     * in order to customize the interface
     */
    builder = gui_open_builder();
    if (builder == NULL)
        return 1;

    /*
     * Store is for adding a client in client side.
     * text_view is for adding a log.
     */
    store = gtk_list_store_new(NUM_COLS, G_TYPE_STRING, G_TYPE_STRING);
    text_view = GTK_TEXT_VIEW(gtk_text_view_new());

    load_interface(builder, text_view, store);

    client_add(store, "0.0.0.0", "Connected");

    /**
     * Adding variables to GUI environnement variable
     */
    gui_env.store = store;
    gui_env.text_view = text_view;

    /**
     * Link widgets to signal handlers
     */
    gui_add_handler(builder, "window", "destroy", gtk_main_quit, &gui_env);
    gui_add_handler(builder, "start", "clicked", start_server, &gui_env);
    gui_add_handler(builder, "stop", "clicked", stop_server, &gui_env);
    gui_add_handler(builder, "connect", "clicked", client_connect, &gui_env);

    GObject *window = gtk_builder_get_object(builder, "window");

    /*
     * All the interface changes have to be done before that function !
     */
    gtk_widget_show_all(GTK_WIDGET(window));
    gtk_main();

    return 0;
}

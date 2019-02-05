#include "database/db.h"
#include "database/db_initializer.h"
#include "gui/builder.h"
#include "gui/client.h"
#include "gui/loader.h"
#include "handlers/tcp.h"
#include "handlers/clients_events.h"
#include <gtk/gtk.h>

int
main(int argc, char **argv)
{
    Database *db;
    GuiEnv gui_env;

    GtkBuilder *builder;
    GtkTextView *text_view;
    GtkListStore *store;
    GtkWidget *client_tree;

    GObject *window;

    db = db_open();
    db_init(db);

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
    client_tree = gtk_tree_view_new();
    store = gtk_list_store_new(NUM_COLS, G_TYPE_STRING, G_TYPE_STRING);
    text_view = GTK_TEXT_VIEW(gtk_text_view_new());

    load_interface(builder, text_view, store, client_tree);

    /**
     * Adding variables to GUI environnement variable
     */
    gui_env.client_tree = client_tree;
    gui_env.store = store;
    gui_env.text_view = text_view;

    /**
     * Link widgets to signal handlers
     */
    gui_add_handler(builder, "window", "destroy", gtk_main_quit, &gui_env);
    gui_add_handler(builder, "start", "clicked", start_server, &gui_env);
    gui_add_handler(builder, "stop", "clicked", stop_server, &gui_env);
    gui_add_handler(builder, "connect", "clicked", client_connect, &gui_env);

    g_signal_connect(client_tree, "button-press-event", (GCallback)trigger_clients_button_press, gui_env.text_view);
    g_signal_connect(client_tree, "popup-menu", (GCallback)on_popup, text_view);

    window = gtk_builder_get_object(builder, "window");

    client_add(store, "0.0.0.0", 1);

    /*
     * All the interface changes have to be done before that function !
     */
    gtk_widget_show_all(GTK_WIDGET(window));
    gtk_main();

    return 0;
}

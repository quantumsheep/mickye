#include "config.h"
#include "database/db.h"
#include "database/db_initializer.h"
#include "gui/builder.h"
#include "gui/client.h"
#include "gui/loader.h"
#include "handlers/clients_events.h"
#include "handlers/tcp.h"
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

    /**
     * Generate the CONFIG super global
     */
    config_update();

    // Initialize the database
    db = db_open();
    db_init(db);

    // Initialize gtk
    gtk_init(&argc, &argv);

    // Create a GTKBuilder if the builder can't be created, return 1
    builder = gui_open_builder();
    if (builder == NULL)
    {
        return 1;
    }

    // Creatin the client_tree (for listing the clients), the store (the client tree model of a listed client) and the text_view (text of the logs)
    client_tree = gtk_tree_view_new();
    store = gtk_list_store_new(NUM_COLS, G_TYPE_STRING, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING);
    text_view = GTK_TEXT_VIEW(gtk_text_view_new());

    // Loading the interface
    load_interface(builder, text_view, store, client_tree);

    // Adding importants variables to gui_env (the three, her model, and the logs text view)
    gui_env.client_tree = client_tree;
    gui_env.store = store;
    gui_env.text_view = text_view;

    // Link the main_windown, the start, stop and connect button to her events
    gui_add_handler(builder, "window", "destroy", gtk_main_quit, &gui_env);
    gui_add_handler(builder, "start", "clicked", start_server, &gui_env);
    gui_add_handler(builder, "stop", "clicked", stop_server, &gui_env);
    gui_add_handler(builder, "connect", "clicked", client_connect, &gui_env);

    // Link the client list to a pop menu event
    g_signal_connect(client_tree, "button-press-event", (GCallback)trigger_clients_button_press, &gui_env);
    g_signal_connect(client_tree, "popup-menu", (GCallback)on_popup, &gui_env);

    // Catch the main_window object and the her position to the center of the screen
    window = gtk_builder_get_object(builder, "window");
    gtk_window_set_position((GtkWindow *)window, GTK_WIN_POS_CENTER);

    // Show the main window and all her child widgets
    gtk_widget_show_all(GTK_WIDGET(window));
    gtk_main();

    return 0;
}

#include "gui/gui.h"
#include "handlers/tcp.h"
#include <vte/vte.h>

enum
{
    COL_NAME = 0,
    COL_STATUS,
    NUM_COLS
};

void
load_clients(GtkBuilder *builder, GtkListStore *store)
{
    GtkWidget *client_tree;
    GObject *client_scroll;
    GtkCellRenderer *renderer;

    client_scroll = gtk_builder_get_object(builder, "clients");

    client_tree = gtk_tree_view_new();

    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_insert_column_with_attributes(
        GTK_TREE_VIEW(client_tree), -1, "IP", renderer, "text", COL_NAME, NULL);

    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(client_tree), -1,
                                                "STATUS", renderer, "text",
                                                COL_STATUS, NULL);

    gtk_tree_view_set_model(GTK_TREE_VIEW(client_tree), GTK_TREE_MODEL(store));

    gtk_container_add(GTK_CONTAINER(client_scroll), client_tree);
}

void
load_terminal(GtkBuilder *builder)
{
    gchar **envp, **command;
    GObject *terminal;

    envp = g_get_environ();
    command = (gchar *[]){g_strdup(g_environ_getenv(envp, "SHELL")), NULL};
    g_strfreev(envp);

    terminal = gtk_builder_get_object(builder, "terminal");
    vte_terminal_spawn_sync(VTE_TERMINAL(terminal), VTE_PTY_DEFAULT,
                            NULL,       /* working directory  */
                            command,    /* command */
                            NULL,       /* environment */
                            0,          /* spawn flags */
                            NULL, NULL, /* child setup */
                            NULL,       /* child pid */
                            NULL, NULL);
}

void
load_logs(GtkBuilder *builder, GtkWidget *text_view)
{
    GObject *text_view_scroll;

    text_view_scroll = gtk_builder_get_object(builder, "logs");

    gtk_container_add(GTK_CONTAINER(text_view_scroll), text_view);

    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), 0);
}

void
load_interface(GtkBuilder *builder, GtkWidget *text_view, GtkListStore *store)
{
    load_clients(builder, store);
    load_terminal(builder);
    load_logs(builder, text_view);

    log_add(text_view, "Finished loading", "interface");
}

int
main(int argc, char **argv)
{
    GtkBuilder *builder;
    GtkWidget *text_view;
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

    /**
     * Link widgets to signal handlers
     */
    gui_add_handler(builder, "window", "destroy", gtk_main_quit);
    gui_add_handler(builder, "start", "clicked", start_server);
    gui_add_handler(builder, "stop", "clicked", gtk_main_quit);
    gui_add_handler(builder, "connect", "clicked", client_connect);

    /*
     * Store is for adding a client in client side.
     * text_view is for adding a log.
     */
    store = gtk_list_store_new(NUM_COLS, G_TYPE_STRING, G_TYPE_STRING);
    text_view = gtk_text_view_new();

    load_interface(builder, text_view, store);

    GObject *window = gtk_builder_get_object(builder, "window");

    client_add(store, "0.0.0.0", "Connected");

    /*
     * All the interface changes have to be done before that function !
     */
    gtk_widget_show_all(GTK_WIDGET(window));
    gtk_main();

    return 0;
}

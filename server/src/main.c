#include "gui/gui.h"
#include "handlers/tcp.h"
#include <vte/vte.h>

void
load_clients(GObject *main_parent_object, gint left, gint top, gint width,
             gint height)
{
    GtkWidget *client_scroll = gtk_scrolled_window_new(NULL, NULL);

    gtk_grid_attach(GTK_GRID(main_parent_object), client_scroll, left, top, width, height);
    gtk_widget_show_all(client_scroll);
}

void
load_terminal(GObject *main_parent_object, gint left, gint top, gint width,
              gint height)
{
    gchar **envp = g_get_environ();
    gchar **command =
        (gchar *[]){g_strdup(g_environ_getenv(envp, "SHELL")), NULL};
    g_strfreev(envp);

    GtkWidget *terminal = vte_terminal_new();

    vte_terminal_spawn_sync(VTE_TERMINAL(terminal), VTE_PTY_DEFAULT,
                            NULL,       /* working directory  */
                            command,    /* command */
                            NULL,       /* environment */
                            0,          /* spawn flags */
                            NULL, NULL, /* child setup */
                            NULL,       /* child pid */
                            NULL, NULL);

    gtk_grid_attach(GTK_GRID(main_parent_object), terminal, left, top, width,
                    height);
    gtk_widget_show_all(terminal);
}

void
load_logs(GObject *main_parent_object, GtkWidget *text_view, gint left,
          gint top, gint width, gint height)
{
    GtkWidget *text_view_scroll = gtk_scrolled_window_new(NULL, NULL);

    gtk_container_add(GTK_CONTAINER(text_view_scroll), text_view);

    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), 0);
    gtk_grid_attach(GTK_GRID(main_parent_object), text_view_scroll, left, top,
                    width, height);
    gtk_widget_show_all(text_view_scroll);
}

void
load_interface(GObject *main_parent_object)
{
    load_clients(main_parent_object, 0, 4, 4, 1);
    load_terminal(main_parent_object, 0, 5, 4, 3);

    GtkWidget *text_view = gtk_text_view_new();
    load_logs(main_parent_object, text_view, 0, 12, 4, 3);

    log_create(text_view, "Finished loading", "interface");
}

int
main(int argc, char **argv)
{
    GtkBuilder *builder;

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
    // gui_add_handler(builder, "terminal", "clicked", call_clients_list);
    gui_add_handler(builder, "quit", "clicked", gtk_main_quit);

    // Getting the main grid object from builder.ui
    GObject *main_grid = gtk_builder_get_object(builder, "grid");

    load_interface(main_grid);
    gtk_main();

    return 0;
}

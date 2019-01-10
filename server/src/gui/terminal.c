#include "terminal.h"
#include <vte/vte.h>

void call_terminal()
{
    // create_window("Terminal", 800, 600);
    // error_modal("Ceci est un message d'erreur");

    GtkWidget *terminal = vte_terminal_new();
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Terminal");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 200);

    gchar **envp = g_get_environ();
    gchar **command = (gchar *[]){g_strdup(g_environ_getenv(envp, "SHELL")), NULL};
    g_strfreev(envp);

    vte_terminal_spawn_sync(VTE_TERMINAL(terminal),
                            VTE_PTY_DEFAULT,
                            NULL,       /* working directory  */
                            command,    /* command */
                            NULL,       /* environment */
                            0,          /* spawn flags */
                            NULL, NULL, /* child setup */
                            NULL,       /* child pid */
                            NULL, NULL);

    g_signal_connect(window, "delete-event", gtk_main_quit, NULL);
    g_signal_connect(terminal, "child-exited", gtk_main_quit, NULL);

    gtk_container_add(GTK_CONTAINER(window), terminal);
    gtk_widget_show_all(window);
}
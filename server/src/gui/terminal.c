#include "terminal.h"
#include <vte/vte.h>

void
call_terminal()
{
    GtkWidget *terminal;
    GtkWidget *window;

    gchar **envp;
    gchar **command;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Terminal");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 200);

    envp = g_get_environ();
    command = (gchar *[]){g_strdup(g_environ_getenv(envp, "SHELL")), NULL};
    g_strfreev(envp);

    terminal = vte_terminal_new();
    vte_terminal_spawn_sync(VTE_TERMINAL(terminal), VTE_PTY_DEFAULT,
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
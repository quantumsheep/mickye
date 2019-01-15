#include "loader.h"

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
load_logs(GtkBuilder *builder, GtkTextView *text_view)
{
    GObject *text_view_scroll;

    text_view_scroll = gtk_builder_get_object(builder, "logs");
    gtk_container_add(GTK_CONTAINER(text_view_scroll), GTK_WIDGET(text_view));

    gtk_text_view_set_editable(text_view, 0);
}

void
load_interface(GtkBuilder *builder, GtkTextView *text_view, GtkListStore *store)
{
    load_clients(builder, store);
    load_terminal(builder);
    load_logs(builder, text_view);

    log_add(text_view, "Finished loading", "interface");
}
#include "terminal.h"

GtkWidget *entry;
GtkWidget *text_view;
GtkWidget *window;

GuiEnv *_env = NULL;

TcpClient *_selected_client;

void
terminal_destroy()
{
    if (entry != NULL && window != NULL)
    {
        gtk_window_close(GTK_WINDOW(window));
    }
}

void
insert_entry(char *text)
{
    GtkTextBuffer *buffer;
    GtkTextIter end;

    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    gtk_text_buffer_get_end_iter(buffer, &end);
    gtk_text_buffer_insert(buffer, &end, text, strlen(text));
}

void
terminal_send_to_client()
{
    GtkEntryBuffer *buf;
    char *text;

    buf = gtk_entry_get_buffer(GTK_ENTRY(entry));
    text = (char *)gtk_entry_buffer_get_text(buf);

    insert_entry("$ ");
    insert_entry(text);
    insert_entry("\n");

    if (write(_selected_client->socket, text, strlen(text)) == -1)
    {
        puts(strerror(errno));
    }

    gtk_entry_buffer_delete_text(buf, 0, strlen(text));
}

void *
terminal_listen_client(void *args, GuiEnv *env)
{
    GtkTreeSelection *selection;
    GtkTreeIter iter;
    GtkTreeModel *model;
    GtkTreeView *client_tree;
    GValue value = G_VALUE_INIT;
    char data[TCP_CHUNK_SIZE];
    ssize_t received;

    while (1)
    {
        received = read(_selected_client->socket, data, TCP_CHUNK_SIZE);

        if (received > 0)
        {
            insert_entry(data);
        }
        else
        {
            break;
        }
    }

    terminal_destroy();
    delete_client(NULL, _env);

    log_add(_env->text_view, "Client exited", "Stopping terminal...");
    pthread_exit(NULL);
    return NULL;
}

void
set_terminal_colors(GtkWidget *entry, GtkWidget *text_view)
{
    GtkStyleContext *context;
    GtkCssProvider *provider;

    context = gtk_widget_get_style_context(entry);
    provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(GTK_CSS_PROVIDER(provider),
                                    "entry {\n"
                                    "   color: lightgreen;\n"
                                    "   background-color: black;\n"
                                    "   border-color: green;\n"
                                    "   border-radius: 0;\n"
                                    "}\n",
                                    -1, NULL);
    gtk_style_context_add_provider(context,
                                   GTK_STYLE_PROVIDER(provider),
                                   GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    context = gtk_widget_get_style_context(text_view);
    provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(GTK_CSS_PROVIDER(provider),
                                    "textview text{\n"
                                    "   color: lightgreen;\n"
                                    "   background-color: black;\n"
                                    "}\n",
                                    -1, NULL);
    gtk_style_context_add_provider(context,
                                   GTK_STYLE_PROVIDER(provider),
                                   GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    g_object_unref(provider);
}

void
terminal_start(TcpClient *client, GuiEnv *env)
{
    pthread_t thread;

    GtkWidget *box;
    GtkWidget *scrollbar;

    terminal_destroy();

    _env = env;
    _selected_client = client;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), client->ipv4);
    gtk_window_set_default_size(GTK_WINDOW(window), TERMINAL_DEFAULT_WIDTH, TERMINAL_DEFAULT_HEIGH);
    gtk_window_set_position((GtkWindow *)window, GTK_WIN_POS_CENTER);

    box = gtk_box_new(TRUE, 0);
    gtk_container_add(GTK_CONTAINER(window), box);

    scrollbar = gtk_scrolled_window_new(NULL, NULL);

    text_view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);

    gtk_container_add(GTK_CONTAINER(scrollbar), text_view);
    gtk_box_pack_start(GTK_BOX(box), scrollbar, TRUE, TRUE, 0);

    /**
     * Read client's output
     */
    pthread_create(&thread, NULL, terminal_listen_client, env);

    /**
     * Read terminal input
     */
    entry = gtk_entry_new();
    g_signal_connect(entry, "activate", terminal_send_to_client, NULL);

    gtk_box_pack_end(GTK_BOX(box), entry, FALSE, FALSE, 0);

    set_terminal_colors(entry, text_view);

    gtk_widget_show_all(window);
}
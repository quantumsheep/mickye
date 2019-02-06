#include "terminal.h"

GtkWidget *entry;
GtkWidget *text_view;
GtkWidget *window;
GuiEnv *_env = NULL;
TcpClient *_selected_client;

/*
*   Function to remove a gtk terminal window
*/
void
terminal_destroy()
{
    if (window != NULL)
    {
        // Close the window
        gtk_window_close(GTK_WINDOW(window));
    }
}

/*
*   Function to insert a text (char*) into the terminal entry of a client
*   
*   @param      text       the text to insert
*/
void
insert_entry(char *text)
{
    GtkTextBuffer *buffer;
    GtkTextMark *mark;
    GtkTextIter end;

    // Get the actual buffer for the entry opened and in sert the text
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    gtk_text_buffer_get_end_iter(buffer, &end);
    gtk_text_buffer_insert(buffer, &end, text, strlen(text));

    mark = gtk_text_buffer_get_insert(buffer);

    // Set the iter to the new end and move the scrollbar to the new end
    gtk_text_view_scroll_to_mark((GtkTextView *)text_view, mark, 0.0, TRUE, 0.5, 1);
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
    char data[TCP_CHUNK_SIZE];
    ssize_t received;
    GtkTreeIter iter;
    GtkTreeModel *model;
    GtkTreeView *client_tree;
    GValue value = G_VALUE_INIT;
    int client_id;

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

    // Initialize the client_tree and the model from data
    client_tree = GTK_TREE_VIEW(_env->client_tree);
    model = gtk_tree_view_get_model(client_tree);

    // If the first iter exist, set it, check if the socket is the same as terminal, if yes delete it, else check the next iter etc...
    if (gtk_tree_model_get_iter_first(model, &iter))
    {
        gtk_tree_model_get_value(model, &iter, 1, &value);
        client_id = g_value_get_int(&value);
        g_value_unset(&value);

        if (client_id == _selected_client->socket)
        {
            gtk_list_store_remove((GtkListStore *)_env->store, &iter);
        }
        else
        {
            while (gtk_tree_model_iter_next(model, &iter))
            {
                gtk_tree_model_get_value(model, &iter, 1, &value);
                client_id = g_value_get_int(&value);
                g_value_unset(&value);

                if (client_id == _selected_client->socket)
                {
                    gtk_list_store_remove((GtkListStore *)_env->store, &iter);
                }
            };
        }
    }

    log_add(_env->text_view, "Client exited", "Stopping terminal...");
    pthread_exit(NULL);
    return NULL;
}

/*
*   Function to set the colors of a new terminal
*   
*   @param      entry           the entry of the terminal
*   @param      text_view       the textview of the terminal
*/
void
set_terminal_colors(GtkWidget *entry, GtkWidget *text_view)
{
    GtkStyleContext *context;
    GtkCssProvider *provider;

    // Setting up the context style of the entry
    context = gtk_widget_get_style_context(entry);

    // Creating the CSS style for the entry
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
    g_object_unref(provider);

    // Setting up the context style of the text_view
    context = gtk_widget_get_style_context(text_view);

    // Creating the CSS style for the text_view
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

/*
*   Function to start a new terminal for a selected client
*   
*   @param      client      the selected client already set
*   @param      env         GuiEnv env set in main
*/
void
terminal_start(TcpClient *client, GuiEnv *env)
{
    pthread_t thread;
    GtkWidget *box;
    GtkWidget *scrollbar;

    // Removing the past terminal window from gtk if exist
    terminal_destroy();

    // Setting up global variables
    _env = env;
    _selected_client = client;

    // Creating a new GTK window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), client->ipv4);
    gtk_window_set_default_size(GTK_WINDOW(window), TERMINAL_DEFAULT_WIDTH, TERMINAL_DEFAULT_HEIGH);
    gtk_window_set_position((GtkWindow *)window, GTK_WIN_POS_CENTER);

    // Setting up a new box container in the window
    box = gtk_box_new(TRUE, 0);
    gtk_container_add(GTK_CONTAINER(window), box);

    // Creating a scrollbar
    scrollbar = gtk_scrolled_window_new(NULL, NULL);

    // Creating the text_view
    text_view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);

    // Adding the textview to the scrollbar container, adding the scrollbar container to the start of the box container
    gtk_container_add(GTK_CONTAINER(scrollbar), text_view);
    gtk_box_pack_start(GTK_BOX(box), scrollbar, TRUE, TRUE, 0);

    // Create entry of the terminal, adding her an event on ENTER and linking it to the end of the box container
    entry = gtk_entry_new();
    g_signal_connect(entry, "activate", terminal_send_to_client, NULL);
    gtk_box_pack_end(GTK_BOX(box), entry, FALSE, FALSE, 0);

    // Setting up the colors of the terminal
    set_terminal_colors(entry, text_view);

    // Read client output
    pthread_create(&thread, NULL, (void *)terminal_listen_client, env);

    // Set the user focus on the entry
    gtk_widget_grab_focus(entry);

    gtk_widget_show_all(window);
}
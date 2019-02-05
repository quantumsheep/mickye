#include "terminal.h"

GtkWidget *entry;
GtkWidget *text_view;
GtkWidget *window;

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
return_entry()
{
    GtkEntryBuffer *Entrybuffer;
    char *text;

    printf("\noui");

    Entrybuffer = gtk_entry_get_buffer(GTK_ENTRY(entry));
    text = (char*)gtk_entry_buffer_get_text(Entrybuffer);

    insert_entry(text);

    gtk_entry_buffer_delete_text(Entrybuffer, 0, strlen(text));
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
call_terminal(char *title, int width, int height)
{
    if(text_view != NULL && entry != NULL && window != NULL){
        gtk_widget_destroy(text_view);
        gtk_widget_destroy(entry);
        gtk_window_close(GTK_WINDOW(window));
    }
    GtkWidget *box;
    GtkWidget *scrollbar;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), title);
    gtk_window_set_default_size(GTK_WINDOW(window), width, height);

    box = gtk_box_new(TRUE, 0);
    gtk_container_add(GTK_CONTAINER(window), box);

    scrollbar = gtk_scrolled_window_new(NULL, NULL);

    text_view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);

    gtk_container_add(GTK_CONTAINER(scrollbar), text_view);
    gtk_box_pack_start(GTK_BOX(box), scrollbar, TRUE, TRUE, 0);

    entry = gtk_entry_new();
    g_signal_connect(entry, "activate", return_entry, NULL);

    gtk_box_pack_end(GTK_BOX(box), entry, FALSE, FALSE, 0);

    set_terminal_colors(entry, text_view);

    gtk_widget_show_all(window);
}
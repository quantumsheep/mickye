#include "terminal.h"

GtkWidget *entry;
GtkEntryBuffer *Entrybuffer;

void
return_entry()
{
    gchar *text;

    text = gtk_entry_buffer_get_text(Entrybuffer);

    puts(text);
    gtk_entry_buffer_delete_text(Entrybuffer, 0, strlen(text));
}

void
call_terminal(char *title, int width, int height)
{
    GtkTextBuffer *buffer;
    GtkWidget *window;
    GtkWidget *box;
    GtkWidget *text;
    GtkWidget *scrollbar;
    GdkColor color;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), title);
    gtk_window_set_default_size(GTK_WINDOW(window), width, height);
    g_signal_connect(window, "child-exited", gtk_main_quit, NULL);

    box = gtk_box_new(TRUE, 0);
    gtk_container_add(GTK_CONTAINER(window), box);

    scrollbar = gtk_scrolled_window_new(NULL, NULL);

    text = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text), FALSE);
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text));
    gtk_text_buffer_set_text(buffer, "Hello, this is some text", -1);

    gdk_color_parse("lightgreen", &color);
    gtk_widget_modify_fg(text, GTK_STATE_NORMAL, &color);
    gdk_color_parse("black", &color);
    gtk_widget_modify_bg(text, GTK_STATE_NORMAL, &color);

    gtk_container_add(GTK_CONTAINER(scrollbar), text);
    gtk_box_pack_start(GTK_BOX(box), scrollbar, TRUE, TRUE, 0);

    entry = gtk_entry_new();
    g_signal_connect(entry, "activate", return_entry, NULL);

    gdk_color_parse("lightgreen", &color);
    gtk_widget_modify_fg(entry, GTK_STATE_NORMAL, &color);
    gdk_color_parse("black", &color);
    gtk_widget_modify_bg(entry, GTK_STATE_NORMAL, &color);
    Entrybuffer = gtk_entry_get_buffer(entry);

    gtk_box_pack_end(GTK_BOX(box), entry, FALSE, FALSE, 0);

    gtk_widget_show_all(window);
}
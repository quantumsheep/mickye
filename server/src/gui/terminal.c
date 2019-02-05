#include "terminal.h"

GtkWidget *entry;
GtkWidget *text_view;

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

    Entrybuffer = gtk_entry_get_buffer(GTK_ENTRY(entry));
    text = (char*)gtk_entry_buffer_get_text(Entrybuffer);

    insert_entry(text);
    
    gtk_entry_buffer_delete_text(Entrybuffer, 0, strlen(text));
}

void set_terminal_colors(GtkWidget *widget){
    GdkColor color;

    gdk_color_parse("lightgreen", &color);
    gtk_widget_modify_fg(widget, GTK_STATE_NORMAL, &color);
    gdk_color_parse("black", &color);
    gtk_widget_modify_bg(widget, GTK_STATE_NORMAL, &color);
}

void
call_terminal(char *title, int width, int height)
{
    GtkWidget *window;
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

    set_terminal_colors(text_view);
    set_terminal_colors(entry);

    gtk_widget_show_all(window);
}
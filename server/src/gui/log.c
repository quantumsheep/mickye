#include "log.h"

void
log_add(GtkTextView *text_view, char *info_str, char *ip_str)
{
    time_t t;
    struct tm *now;
    GtkTextBuffer *buffer;
    GtkCssProvider *provider;
    GtkStyleContext *context;
    GtkTextMark *mark;
    GtkTextIter iter;
    char *log_message;

    log_message = (char *)malloc(sizeof(char) * (strlen(info_str) + strlen(ip_str) + 16));
    t = time(NULL);
    now = localtime(&t);

    sprintf(log_message, "%s - %s - %02d:%02d:%02d\n", info_str, ip_str, now->tm_hour, now->tm_min, now->tm_sec);

    buffer = gtk_text_view_get_buffer(text_view);
    mark = gtk_text_buffer_get_mark(buffer, "end");

    if (mark == NULL)
    {
        mark = gtk_text_buffer_get_insert(buffer);
        gtk_text_buffer_get_iter_at_mark(buffer, &iter, mark);

        gtk_text_buffer_insert(buffer, &iter, log_message, -1);
        gtk_text_buffer_create_mark(buffer, "end", &iter, 0);
    }
    else
    {
        gtk_text_buffer_get_iter_at_mark(buffer, &iter, mark);
        gtk_text_buffer_insert(buffer, &iter, log_message, strlen(log_message));

        gtk_text_buffer_move_mark_by_name(buffer, "end", &iter);
    }

    // Change default font and color throughout the widget
    provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider,
                                    "textview {"
                                    " font: 15px serif;"
                                    "}",
                                    -1, NULL);
    context = gtk_widget_get_style_context(GTK_WIDGET(text_view));
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    /* Change left margin throughout the widget */
    gtk_text_view_set_left_margin(text_view, 10);

    free(log_message);
}
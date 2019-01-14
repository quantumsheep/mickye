#include "log.h"

void
log_add(GtkWidget *text_view, char *info_str, char *ip_str)
{
    GtkTextBuffer *buffer;
    GtkCssProvider *provider;
    GtkStyleContext *context;
    char log_message[1000];

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    sprintf(log_message, "%s - %s - %d:%d:%d\n", info_str, ip_str, tm.tm_hour,
            tm.tm_min, tm.tm_sec);

    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    gtk_text_buffer_insert_at_cursor(buffer, log_message, -1);
    // Change default font and color throughout the widget
    provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider,
                                    "textview {"
                                    " font: 15px serif;"
                                    "}",
                                    -1, NULL);
    context = gtk_widget_get_style_context(text_view);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider),
                                   GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    /* Change left margin throughout the widget */
    gtk_text_view_set_left_margin(GTK_TEXT_VIEW(text_view), 10);
}
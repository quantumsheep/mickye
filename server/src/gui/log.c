#include "log.h"

static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

/*
*   Function to add a log in the log widget (window).
*   Asking for :
*   @param      text_view       the main text_view of the log widget
*   @param      info_str        a char* corresponding to the displayed info
*   @param      subject_str     a second char* corresponding to another displayed info (most of a subject like)
*/
void
log_add(GtkTextView *text_view, char *info_str, char *subject_str)
{
    GtkTextBuffer *buffer;
    GtkCssProvider *provider;
    GtkStyleContext *context;
    GtkTextMark *mark;
    GtkTextIter iter;
    time_t t;
    struct tm *now;
    char *log_message;
    FILE *log_file;

    //Allocating the message
    log_message = (char *)malloc(sizeof(char) * (strlen(info_str) + strlen(subject_str) + 16));

    //Initializing the time (for random function)
    t = time(NULL);
    now = localtime(&t);

    //Creating the concatened log_message
    sprintf(log_message, "%s %s - %02d:%02d:%02d\n", info_str, subject_str, now->tm_hour, now->tm_min, now->tm_sec);

    //Initializing the text buffer and the position (mark) at the end of the buffer who already exist
    buffer = gtk_text_view_get_buffer(text_view);
    mark = gtk_text_buffer_get_mark(buffer, "end");

    //If the mark was never been initialized, generate one at 0, and insert the text (buffer) at the mark (0 or the start of the buffer)
    //Else if the mark isnt NULL (have already been initialized), insert the text (buffer) at the mark (the end of the buffer)
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

    //Change the default font with CSS, of the log text_view
    provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider,
                                    "textview {"
                                    " font: 15px serif;"
                                    "}",
                                    -1, NULL);
    context = gtk_widget_get_style_context(GTK_WIDGET(text_view));
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    //Change the left margin in the text_view
    gtk_text_view_set_left_margin(text_view, 10);

    //Adding a mutex to prevent colliding logs add
    pthread_mutex_lock(&lock);

    //Create a log file and insert the log at the end
    log_file = fopen(CONFIG(CONFIG_LOG_PATH, CONFIG_LOG_PATH_DEFAULT), "a");
    if (log_file != NULL)
    {
        fwrite(log_message, sizeof(char), strlen(log_message), log_file);
        fclose(log_file);
    }

    //Removing the mutex
    pthread_mutex_unlock(&lock);

    free(log_message);
}
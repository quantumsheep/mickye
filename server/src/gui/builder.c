#include "builder.h"

typedef struct gui_callback_params_t GUICallbackParams;
struct gui_callback_params_t
{
    void (*f)(GtkWidget *, GtkBuilder *, GuiEnv *);
    GtkBuilder *builder;
    void *data;
};

static void
_gui_caller(GtkWidget *widget, gpointer data)
{
    GUICallbackParams *params = data;
    params->f(widget, params->builder, params->data);
}

void
gui_add_handler(GtkBuilder *builder, char *id, char *on, void(*callback), GuiEnv *data)
{
    GUICallbackParams *params;
    GObject *obj;

    params = (GUICallbackParams *)malloc(sizeof(GUICallbackParams));
    params->builder = builder;
    params->f = callback;
    params->data = data;

    obj = gtk_builder_get_object(builder, id);

    if (obj != NULL)
        g_signal_connect(obj, on, G_CALLBACK(_gui_caller), params);
}

GtkBuilder *
gui_open_builder()
{
    GtkBuilder *builder;
    GError *error = NULL;

    builder = gtk_builder_new();

    if (gtk_builder_add_from_file(builder, BUILDER_PATH, &error) == 0)
    {
        g_printerr("Error loading file: %s\n", error->message);
        g_clear_error(&error);

        return NULL;
    }

    return builder;
}

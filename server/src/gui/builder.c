#include "builder.h"

typedef struct gui_callback_params_t GUICallbackParams;
struct gui_callback_params_t
{
    void (*f)(GtkWidget *, GtkBuilder *, GuiEnv *);
    GtkBuilder *builder;
    void *data;
};

/**
 *  gui_add_handler's event callback middleware
 */
static void
_gui_caller(GtkWidget *widget, GUICallbackParams *params)
{
    params->f(widget, params->builder, params->data);
}

/**
 *  Define an event to a GUI element
 * 
 *  @param      builder         the builder
 *  @param      id              the element id
 *  @param      on              the event to listen to
 *  @param      callback        the callback
 *  @param      data            a GuiEnv object (will be passed in the callback)
 */
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

/**
 *  Get a builder from the user interface definition file
 */
GtkBuilder *
gui_open_builder()
{
    GtkBuilder *builder;
    GError *error = NULL;

    builder = gtk_builder_new();

    if (gtk_builder_add_from_file(builder, CONFIG(CONFIG_BUILDER_PATH, CONFIG_BUILDER_PATH_DEFAULT), &error) == 0)
    {
        g_printerr("Error loading file: %s\n", error->message);
        g_clear_error(&error);

        return NULL;
    }

    return builder;
}

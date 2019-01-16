#ifndef _GUI_ENV_H
#define _GUI_ENV_H

#include <gtk/gtk.h>

typedef struct gui_env_t GuiEnv;
struct gui_env_t
{
    GtkListStore *store;
    GtkTextView *text_view;
    void *data;
};

#define GUI_ENV_DATA(data) ((void *)data)

#endif

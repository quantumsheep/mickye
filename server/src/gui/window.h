#ifndef _GUI_WINDOW_H
#define _GUI_WINDOW_H

#include <gtk/gtk.h>

void
create_window(char *title, int width, int height);

void
error_modal(char *error_message);

#endif

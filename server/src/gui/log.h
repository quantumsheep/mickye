#ifndef _GUI_LOG_H
#define _GUI_LOG_H

#include <gtk/gtk.h>
#include <string.h>
#include <time.h>

void
log_add(GtkWidget *view, char *info_str, char *ip_str);

#endif
#ifndef _GUI_LOG_H
#define _GUI_LOG_H

#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

void
log_add(GtkTextView *view, char *info_str, char *ip_str);

#endif

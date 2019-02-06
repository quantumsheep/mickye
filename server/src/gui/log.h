#ifndef _GUI_LOG_H
#define _GUI_LOG_H

#include <gtk/gtk.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../config.h"

#define CONFIG_LOG_PATH "log_path"
#define CONFIG_LOG_PATH_DEFAULT "log.txt"

void
log_add(GtkTextView *view, char *info_str, char *ip_str);

#endif

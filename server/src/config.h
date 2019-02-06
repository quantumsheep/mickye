#ifndef _CONFIG_H
#define _CONFIG_H

#include <stdlib.h>
#include <string.h>

#include "file/file.h"

#define CONFIG_PATH "options.conf"

#define CONFIG(key) (config_get(key))

typedef struct config_t Config;
struct config_t
{
    char *key;
    char *value;

    Config *next;
};

void
config_update();

char *
config_get(char *key);

void
config_set(char *key, char *value);

#endif

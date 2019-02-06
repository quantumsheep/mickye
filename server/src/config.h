#ifndef _CONFIG_H
#define _CONFIG_H

#include <stdlib.h>
#include <string.h>

#include "file/file.h"
#include "streams/console.h"

#define CONFIG_PATH "options.conf"

#define CONFIG(key, dflt) (config_get(key, dflt, 0))
#define CONFIG_ENSURE(key) (config_get(key, NULL, 1))

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
config_get(char *key, char *dflt, int ensure);

void
config_set(char *key, char *value);

#endif

#include "config.h"

#define CONFIG_DELIM "\n"
#define CONFIG_MAX_LEN 512

Config *_conf;

char *
config_get(char *key)
{
    Config *config = _conf;

    while (config)
    {
        if (strcmp(config->key, key) == 0)
        {
            return config->value;
        }

        config = config->next;
    }

    return NULL;
}

void
config_set(char *key, char *value)
{
    Config *new = (Config *)malloc(sizeof(Config));
    new->key = key;
    new->value = value;
    new->next = _conf;
    _conf = new;
}

void
config_update()
{
    char *config;
    char *line;

    char key[CONFIG_MAX_LEN];
    char value[CONFIG_MAX_LEN];

    config = file_read(CONFIG_PATH);

    line = strtok(config, "\n");

    while (line != NULL)
    {
        memset(key, 0x00, CONFIG_MAX_LEN);
        memset(value, 0x00, CONFIG_MAX_LEN);

        sscanf(line, "%s = %s #%*s", key, value);

        if (strlen(value) > 0)
        {
            config_set(key, value);
        }

        line = strtok(NULL, CONFIG_DELIM);
    }

    free(config);
}

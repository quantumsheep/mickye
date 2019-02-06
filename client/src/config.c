#include "config.h"

#define CONFIG_DELIM "\n"
#define CONFIG_MAX_LEN 512

Config *_conf = NULL;

Config *
config_select(char *key)
{
    Config *config = _conf;

    /**
     * Find the configuration value matching key
     */
    while (config != NULL)
    {
        // printf("%s : %d\n", config->key, strlen(config->key));
        if (strcmp(config->key, key) == 0)
        {
            return config;
        }

        config = config->next;
    }

    return config;
}

char *
config_get(char *key, char *dflt, int ensure)
{
    Config *config;

    config = config_select(key);

    if (config != NULL)
    {
        return config->value;
    }

    /**
     * Crash the app if in ensure mode
     */
    if (ensure)
    {
        console_err("Can't get configuration parameter \"");
        console_err(key);
        console_err("\". Quitting the program...");
        exit(0);
    }

    return dflt;
}

void
config_set(char *key, char *value)
{
    Config *config;

    config = config_select(key);

    if (config != NULL)
    {
        config->value = value;
    }
    else
    {
        config = (Config *)malloc(sizeof(Config));

        config->key = (char *)calloc(sizeof(char), strlen(key));
        config->value = (char *)calloc(sizeof(char), strlen(value));

        strcpy(config->key, key);
        strcpy(config->value, value);

        config->next = _conf;
        _conf = config;
    }
}

void
config_update()
{
    char *config;
    char *line;

    char key[CONFIG_MAX_LEN];
    char value[CONFIG_MAX_LEN];

    config = file_read(CONFIG_PATH);

    if (config == NULL)
    {
        console_err("Configuration file not found: ");
        console_err(CONFIG_PATH);
        console_err(".\nQuitting the program...\n");
        exit(1);
    }

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

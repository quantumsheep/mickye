#include "config.h"

#define CONFIG_DELIM "\n"
#define CONFIG_MAX_LEN 512

Config *_conf = NULL;

/**
 *  Retrieve a configuration object or NULL if the wanted key doesn't exists
 * 
 *  @param       key         configuration key
 */
Config *
config_select(char *key)
{
    Config *config = _conf;

    /**
     * Find the configuration value matching key
     */
    while (config != NULL)
    {
        if (strcmp(config->key, key) == 0)
        {
            return config;
        }

        config = config->next;
    }

    return config;
}

/**
 *  Retrieve a configuration object or NULL if the wanted key doesn't exists
 * 
 *  @param       key         configuration key
 *  @param       dflt        default configuration value, returned if the key is not found in the configuration
 *  @param       ensure      choose if you want to crash the app if the key is not found in the configuration
 */
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
        console_err("\".\nQuitting the program...\n");
        exit(1);
    }

    return dflt;
}

/**
 *  Define a key - value configuration
 * 
 *  @param       key         configuration key
 *  @param       dflt        configuration value
 */
void
config_set(char *key, char *value)
{
    Config *config;

    config = config_select(key);

    if (config != NULL)
    {
        free(config->value);

        config->value = (char *)calloc(sizeof(char), strlen(value));
        strcpy(config->value, value);
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

/**
 *  Update the configuration super global
 *  A way of initializing the configuration file
 */
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

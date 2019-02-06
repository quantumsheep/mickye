#include "file.h"

/**
 *  Get the char length of a file
 * 
 *  @param       f          a file
 */
long
file_size(FILE *f)
{
    long size;
    long origin;

    origin = ftell(f);
    fseek(f, 0, SEEK_END);

    size = ftell(f);

    fseek(f, origin, SEEK_SET);

    return size;
}

/**
 *  Read all the content of a file
 * 
 *  @param       f          the file
 */
char *
file_readall(FILE *f)
{
    long size;
    char *content;

    size = file_size(f);
    content = (char *)malloc(sizeof(char) * size);

    fread(content, sizeof(1), size, f);

    return content;
}

/**
 *  Read all the content of a file
 * 
 *  @param       path       the file's path
 */
char *
file_read(const char *path)
{
    FILE *f;
    char *content = NULL;

    f = fopen(path, "rt");

    if (f != NULL)
    {
        content = file_readall(f);

        fclose(f);
    }

    return content;
}

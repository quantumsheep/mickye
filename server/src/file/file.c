#include "file.h"

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

char *
file_read(const char *path)
{
    FILE *f;
    char *content;

    f = fopen(path, "rt");
    content = file_readall(f);

    fclose(f);

    return content;
}

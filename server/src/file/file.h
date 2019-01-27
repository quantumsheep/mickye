#ifndef _FILE_H
#define _FILE_H

#include <stdio.h>
#include <stdlib.h>

long
file_size(FILE *f);

char *
file_readall(FILE *f);

char *
file_read(const char *path);

#endif

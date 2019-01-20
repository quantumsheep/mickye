#ifndef _SHELL_H
#define _SHELL_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>

typedef struct shell_t Shell;
struct shell_t
{
    int stdin;
    FILE *fstdin;

    int stdout;
    FILE *fstdout;
};

Shell
shell_open();

#endif

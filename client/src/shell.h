#ifndef _SHELL_H
#define _SHELL_H

#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct shell_t Shell;
struct shell_t
{
    __pid_t pid;

    int stdin;
    FILE *fstdin;

    int stdout;
    FILE *fstdout;
};

Shell
shell_open();

void
shell_close(Shell shell);

#endif

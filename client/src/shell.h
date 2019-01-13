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

ssize_t
shell_read(Shell shell, char *store);

ssize_t
shell_write(Shell shell, char *data);

Shell
shell_open();

#include <stdio.h>

typedef struct shell_t Shell;
struct shell_t
{
    int stdin;
    int stdout;
    int stderr;
};

FILE*
open_shell();
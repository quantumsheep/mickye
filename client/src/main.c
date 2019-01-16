#include "shell.h"
#include "tcp.h"

#include <stdio.h>
#include <stdlib.h>

void
use_shell(socket_t socket)
{
    char store[8192];
    memset(store, 0x00, 8192);
    Shell shell = shell_open();
    puts("Done opening the shell");

    char *cmd = "ls\n";
    shell_write(shell, cmd);

    while (shell_read(shell, store))
    {
        puts(store);
    }

    // if(shell == NULL)
    // {
    //     puts("Shell initialization failed.");
    //     return;
    // }
}

int
main(int argc, char **argv)
{
    socket_t socket = -1;

    while (socket == -1)
    {
        puts("Opening socket");
        socket = tcp_open("127.0.0.1", 3000);

        if (socket == -1)
        {
            puts("Socket opening failed");
        }
        else
        {
            puts("Done opening socket!");
            puts("Biding to shell...");

            use_shell(socket);
        }
    }

    return 0;
}

#include "fd.h"
#include "shell.h"
#include "tcp.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

Shell shell;
socket_t sock = -1;

void *
shell_stdin_from_server(void *args)
{
    char store[FD_CHUNK_SIZE];

    while (1)
    {
        memset(store, 0x00, FD_CHUNK_SIZE);

        if (!fd_read(sock, store))
        {
            puts("Server's stream ended...");
            break;
        }

        fd_write(shell.stdin, store);
    }

    puts("Exiting reading...");

    shell_close(shell);
    pthread_exit(NULL);
    return NULL;
}

void *
shell_stdout_to_server(void *args)
{
    char store[FD_CHUNK_SIZE];

    while (1)
    {
        memset(store, 0x00, FD_CHUNK_SIZE);

        if (!fd_read(shell.stdout, store))
        {
            break;
        }

        fd_write(sock, store);
    }

    puts("Exiting writing...");

    pthread_exit(NULL);
    return NULL;
}

void
use_shell()
{
    shell = shell_open();
    puts("Done opening the shell");

    pthread_t thread_recv;
    if (pthread_create(&thread_recv, NULL, shell_stdin_from_server, NULL) != 0)
    {
        puts("Failed to create receiver thread.");
        return;
    }

    pthread_t thread_push;
    if (pthread_create(&thread_push, NULL, shell_stdout_to_server, NULL) != 0)
    {
        puts("Failed to create pusher thread.");
        return;
    }

    pthread_join(thread_recv, NULL);
    pthread_join(thread_push, NULL);
}

int
main(int argc, char **argv)
{
    while (1)
    {
        puts("Try opening a socket connection...");
        sock = tcp_open("127.0.0.1", 3000);

        puts("Connection established!");
        puts("Opening the shell...");

        use_shell();
    }

    return 0;
}

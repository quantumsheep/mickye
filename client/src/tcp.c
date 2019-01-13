#include "tcp.h"

int
tcp_send(socket_t fd, char *data)
{
    return send(fd, data, strlen(data), 0);
}

int
tcp_receive(socket_t fd, char store[TCP_MAX_RECV_LEN])
{
    return recv(fd, store, TCP_MAX_RECV_LEN, 0);
}

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
    if (connect(fd, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        return -1;
    }

    return fd;
}
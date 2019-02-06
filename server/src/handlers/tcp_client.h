#ifndef _HANDLERS_TCP_CLIENT_H
#define _HANDLERS_TCP_CLIENT_H

#include <arpa/inet.h>

typedef struct tcp_client_t TcpClient;
struct tcp_client_t
{
    int socket;
    char ipv4[INET_ADDRSTRLEN];
    char ipv6[INET6_ADDRSTRLEN];
};

typedef struct tcp_client_chain_t TcpClientChain;
struct tcp_client_chain_t
{
    TcpClient *client;

    TcpClientChain *next;
};

#endif

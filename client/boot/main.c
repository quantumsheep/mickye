#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib") // Link de la bibliothèque winsock2 pour compilation avec MINGW

#define PORT 1025
#define HOST "127.0.0.1"

int main(int argc, char **argv)
{
    WSADATA winsock;
    SOCKET sock;
    struct sockaddr_in server;
    char *message, *stream, server_reply[2000];
    int recv_size;

    //Initialisation of winsock2
    printf("\nInitialisation de winsock2...");
    if (WSAStartup(MAKEWORD(2, 2), &winsock) != 0)
    {
        printf("Erreur : %d", WSAGetLastError());
        return 1;
    }

    //Generating a socket
    printf("\nInitialisation de winsock2 ok.");

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
    {
        printf("Impossible de creer un socket : %d", WSAGetLastError());
    }

    printf("\nSocket cree.");

    server.sin_addr.s_addr = inet_addr(HOST);
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);

    int conn = 1;
    stream = "STREAM_SOCK";
    message = "OK";
    while (conn == 1)
    {
        connect(sock, (struct sockaddr *)&server, sizeof(server));
        send(sock, stream, strlen(message), 0);
    }

    //Send data
    message = "HELLO PETITE PUTE.";
    if (send(sock, message, strlen(message), 0) < 0)
    {
        puts("Erreur d'envoi.");
        return 1;
    }
    puts("\nDonnees envoyees");

    //Recepting data
    if ((recv_size = recv(sock, server_reply, 2000, 0)) == SOCKET_ERROR)
    {
        puts("Erreur de reception.");
    }

    puts("\nDonnees recues");

    //adding a \0 at the end of the string to make it correct
    server_reply[recv_size] = '\0';
    puts(server_reply);

    return 0;
}

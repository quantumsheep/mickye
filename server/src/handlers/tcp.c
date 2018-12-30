#include "tcp.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close
#include <pthread.h>

#define TCP_SERVER_PORT 3000

char client_message[2000];
char buffer[1024];
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void*
socketThread(void *arg)
{
    int newSocket = *((int*)arg);
    recv(newSocket, client_message, 2000, 0);

    // Send message to the client socket
    pthread_mutex_lock(&lock);

    char *message = malloc(sizeof(client_message) + 20);

    strcpy(message, "Hello Client : ");
    strcat(message, client_message);
    strcat(message, "\n");
    strcpy(buffer, message);
    free(message);

    pthread_mutex_unlock(&lock);
    sleep(1);
    send(newSocket, buffer, 13, 0);
    printf("Exit socketThread \n");
    close(newSocket);

    pthread_exit(NULL);
}

void*
tcp_init()
{
    int serverSocket, newSocket;
    struct sockaddr_in serverAddr;
    struct sockaddr_storage serverStorage;

    socklen_t addr_size;

    // Create the socket.
    serverSocket = socket(PF_INET, SOCK_STREAM, 0);

    /**
     * Configure server settings
     * 
     * sin_family is Internet
     * sin_port use htons to use the proper byte order
     * sin_addr is the IP address (127.0.0.1 for localhost)
     */
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(TCP_SERVER_PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Set all bits of the padding field to 0
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

    // Bind the address struct to the socket
    bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));

    // Listen on the socket, with 40 max connection requests queued
    if (listen(serverSocket, 50) == 0) 
        printf("Listening\n");
    else
        printf("Error\n");

    pthread_t tid[60];

    int i = 0;
    while (1)
    {
        // Accept call creates a new socket for the incoming connection
        addr_size = sizeof serverStorage;

        newSocket = accept(serverSocket, (struct sockaddr *)&serverStorage, &addr_size);

        // for each client request creates a thread and assign the client request to it to process
        // so the main thread can entertain next request
        if (pthread_create(&tid[i], NULL, socketThread, &newSocket) != 0)
        {
            printf("Failed to create thread\n");
        }

        if (i >= 50)
        {
            i = 0;

            while (i < 50)
            {
                pthread_join(tid[i++], NULL);
            }

            i = 0;
        }
    }
}

void
start_server(GtkWidget *widget, GtkBuilder *builder)
{
    // GObject *stopButton = gtk_builder_get_object(builder, "stop");
    
    gtk_widget_set_sensitive(widget, 0);
    // g_object_set_property(stopButton, "sensitive", "FALSE");
    g_thread_new("TCP", tcp_init, NULL);
}
#include "tcp.h"

#define TCP_SERVER_PORT 3000

char client_message[2000];
char buffer[1024];

GThread *thread;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *
socket_thread(void *arg)
{
    int newSocket;
    char *message;

    newSocket = *((int *)arg);

    while (1)
    {
        recv(newSocket, client_message, 2000, 0);

        // Send message to the client socket
        pthread_mutex_lock(&lock);

        message = (char *)malloc(sizeof(client_message) + 20);

        strcpy(message, "Hello Client : ");
        strcat(message, client_message);
        strcat(message, "\n");
        strcpy(buffer, message);
        free(message);

        pthread_mutex_unlock(&lock);
        sleep(1);
        send(newSocket, buffer, 13, 0);
    }

    pthread_exit(NULL);
}

void *
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

    // Listen on the socket, with 64 max connection requests queued
    listen(serverSocket, 64);
    pthread_t tid[64];

    int i = 0;
    while (1)
    {
        // Accept call creates a new socket for the incoming connection
        addr_size = sizeof serverStorage;

        newSocket = accept(serverSocket, (struct sockaddr *)&serverStorage, &addr_size);

        // for each client request creates a thread and assign the client
        // request to it to process so the main thread can entertain next
        // request
        if (pthread_create(&tid[i], NULL, socket_thread, &newSocket) != 0)
        {
            printf("Failed to create thread\n");
        }

        if (++i >= 64)
        {
            pthread_join(tid[i], NULL);
        }
    }
}

void
start_server(GtkWidget *widget, GtkBuilder *builder, GuiEnv *data)
{
    GObject *stopButton = gtk_builder_get_object(builder, "stop");

    gtk_widget_set_sensitive(widget, 0);
    gtk_widget_set_sensitive(GTK_WIDGET(stopButton), 1);

    thread = g_thread_new("TCP", tcp_init, NULL);

    log_add(data->text_view, "Started", "Server");
}

void
stop_server(GtkWidget *widget, GtkBuilder *builder, GuiEnv *data)
{
    GObject *startButton = gtk_builder_get_object(builder, "start");

    gtk_widget_set_sensitive(widget, 0);

    g_thread_unref(thread);
    gtk_widget_set_sensitive(GTK_WIDGET(startButton), 1);

    log_add(data->text_view, "Stopped", "Server");
}

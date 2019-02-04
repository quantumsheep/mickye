#include "tcp.h"

char buffer[TCP_CHUNK_SIZE];

pthread_t server_thread;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

GuiEnv *env = NULL;

int server_socket;

void
tcp_stop()
{
    tcp_annihilate_socket(server_socket);
}

int
tcp_bind(int socket, struct sockaddr_in *addr)
{
    int val = 1;

    setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
    setsockopt(socket, SOL_SOCKET, SO_REUSEPORT, &val, sizeof(val));

    return bind(socket, (struct sockaddr *)addr, sizeof(*addr));
}

void
tcp_annihilate_socket(int socket)
{
    shutdown(socket, SHUT_RDWR);
    close(socket);
    setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int));
}

void *
socket_thread(void *arg)
{
    TcpClient *client;
    char *message;
    char client_message[TCP_CHUNK_SIZE];
    ssize_t received;

    client = (TcpClient *)arg;

    client_add(env->store, client->ipv4, CLIENT_CONNECTED);

    while (1)
    {
        received = recv(client->socket, client_message, TCP_CHUNK_SIZE, 0);

        if (received == -1)
        {
            break;
        }
        else if (received > 0)
        {
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
            send(client->socket, buffer, strlen(buffer), 0);
        }
    }

    pthread_exit(NULL);
}

int
tcp_create_connection(pthread_t *thread, int socket, struct sockaddr_storage *storage)
{
    TcpClient *client = (TcpClient *)calloc(sizeof(TcpClient), 1);
    struct sockaddr_in *ipv4;
    struct sockaddr_in6 *ipv6;

    ipv4 = (struct sockaddr_in *)storage;
    ipv6 = (struct sockaddr_in6 *)storage;

    memset(client->ipv4, 0x00, INET_ADDRSTRLEN);
    inet_ntop(AF_INET, &(ipv4->sin_addr), client->ipv4, INET_ADDRSTRLEN);

    memset(client->ipv6, 0x00, INET6_ADDRSTRLEN);
    inet_ntop(AF_INET6, &(ipv6->sin6_addr), client->ipv6, INET6_ADDRSTRLEN);

    return pthread_create(thread, NULL, socket_thread, (void *)client);
}

void *
tcp_init()
{
    /**
     * Server informations
     */
    struct sockaddr_in addr;
    struct sockaddr_storage storage;
    socklen_t storage_size;

    /**
     * Client socket file descriptors
     */
    int client_socket = 0;

    /**
     * Number of connected clients
     */
    int connections = 0;

    // Create the socket.
    server_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    printf("%d\n", server_socket);

    /**
     * Configure server settings
     *
     * sin_family is Internet
     * sin_port use htons to use the proper byte order
     * sin_addr is the IP address (127.0.0.1 for localhost)
     */
    addr.sin_family = AF_INET;
    addr.sin_port = htons(TCP_SERVER_PORT);
    addr.sin_addr.s_addr = inet_addr(TCP_SERVER_HOST);

    // Set all bits of the padding field to 0
    memset(addr.sin_zero, 0x00, sizeof(addr.sin_zero));

    // Bind the address struct to the socket
    tcp_bind(server_socket, &addr);

    // Listen on the socket, with 64 max connection requests queued
    listen(server_socket, 64);
    pthread_t tid[64];

    /**
     * Listening loop
     */
    while (1)
    {
        storage_size = sizeof storage;

        client_socket = accept(server_socket, (struct sockaddr *)&storage, &storage_size);

        if (client_socket == -1)
        {
            break;
        }

        if (tcp_create_connection(&tid[connections], client_socket, &storage) != 0)
        {
            printf("Thread N°%d can't be created.", connections);
        }
        else if (++connections >= 64)
        {
            pthread_join(tid[connections - 1], NULL);
        }
    }

    /**
     * Annhilating the sockets
     */
    tcp_annihilate_socket(server_socket);
    while (--connections >= 0)
        tcp_annihilate_socket(tid[connections]);

    puts("stoping server...");
    pthread_exit(NULL);
}

void
start_server(GtkWidget *widget, GtkBuilder *builder, GuiEnv *data)
{
    GObject *stopButton;

    gtk_widget_set_sensitive(widget, 0);

    stopButton = gtk_builder_get_object(builder, "stop");
    gtk_widget_set_sensitive(GTK_WIDGET(stopButton), 1);

    if (env == NULL)
    {
        env = data;
    }

    pthread_create(&server_thread, NULL, tcp_init, NULL);

    log_add(data->text_view, "Started", "Server");
}

void
stop_server(GtkWidget *widget, GtkBuilder *builder, GuiEnv *data)
{
    GObject *startButton;

    gtk_widget_set_sensitive(widget, 0);

    startButton = gtk_builder_get_object(builder, "start");
    gtk_widget_set_sensitive(GTK_WIDGET(startButton), 1);

    tcp_stop();

    log_add(data->text_view, "Stopped", "Server");
}

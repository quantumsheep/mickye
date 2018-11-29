#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib") //Winsock Library

int init()
{
  WSADATA wsa;
  SOCKET master, new_socket, client_socket[30], s;
  struct sockaddr_in server, address;
  int max_clients = 30, activity, addrlen, i, valread;
  char *message = "ECHO Daemon v1.0 \r\n";

  // Size of our received buffer, this is the string length
  int MAXRECV = 1024;

  // Set of socket stream's file descriptor
  fd_set readfds;

  // 1 extra for string termination
  char *buffer = (char *)malloc((MAXRECV + 1) * sizeof(char));

  for (i = 0; i < 30; i++)
  {
    client_socket[i] = 0;
  }

  printf("\nInitialisation de Winsock2...");
  if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
  {
    printf("Erreur. code numéro : %d", WSAGetLastError());
    exit(EXIT_FAILURE);
  }

  printf("Initialisé.\n");

  // Create a socket
  if ((master = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
  {
    printf("Impossible de creer un socket : %d", WSAGetLastError());
    exit(EXIT_FAILURE);
  }

  printf("Socket cree.\n");

  // Prepare the sockaddr_in structure
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons(1025);

  // Bind
  if (bind(master, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
  {
    printf("Error number : %d", WSAGetLastError());
    exit(EXIT_FAILURE);
  }

  puts("Link established");

  // Listen to an incoming connections
  listen(master, 3);

  // Accept and incoming connection
  puts("Waiting for connection...");

  addrlen = sizeof(struct sockaddr_in);

  while (TRUE)
  {
    //clear the socket fd set
    FD_ZERO(&readfds);

    //add master socket to fd set
    FD_SET(master, &readfds);

    //add child sockets to fd set
    for (i = 0; i < max_clients; i++)
    {
      s = client_socket[i];
      if (s > 0)
      {
        FD_SET(s, &readfds);
      }
    }

    //wait for an activity on any of the sockets, timeout is NULL , so wait indefinitely
    activity = select(0, &readfds, NULL, NULL, NULL);

    if (activity == SOCKET_ERROR)
    {
      printf("Error while choosing the callers, error code : %d", WSAGetLastError());
      exit(EXIT_FAILURE);
    }

    //If something happened on the master socket , then its an incoming connection
    if (FD_ISSET(master, &readfds))
    {
      if ((new_socket = accept(master, (struct sockaddr *)&address, (int *)&addrlen)) < 0)
      {
        perror("accepte");
        exit(EXIT_FAILURE);
      }

      //inform user of socket number - used in send and receive commands
      printf("New connection, socket number : %d , ip : %s , port : %d \n", new_socket, inet_ntoa(address.sin_addr), ntohs(address.sin_port));

      //send new connection greeting message
      if (send(new_socket, message, strlen(message), 0) != strlen(message))
      {
        perror("Sending error");
      }

      puts("Welcome message sended with success.");

      //add new socket to array of sockets
      for (i = 0; i < max_clients; i++)
      {
        if (client_socket[i] == 0)
        {
          client_socket[i] = new_socket;
          printf("Adding to the socket list - %d \n", i);
          break;
        }
      }
    }

    //else its some IO operation on some other socket :)
    for (i = 0; i < max_clients; i++)
    {
      s = client_socket[i];
      //if client presend in read sockets
      if (FD_ISSET(s, &readfds))
      {
        //get details of the client
        getpeername(s, (struct sockaddr *)&address, (int *)&addrlen);

        //Check if it was for closing , and also read the incoming message
        //recv does not place a null terminator at the end of the string (whilst printf %s assumes there is one).
        valread = recv(s, buffer, MAXRECV, 0);

        if (valread == SOCKET_ERROR)
        {
          int error_code = WSAGetLastError();
          if (error_code == WSAECONNRESET)
          {
            //Somebody disconnected , get his details and print
            printf("Client disconnected , ip : %s , port : %d \n", inet_ntoa(address.sin_addr), ntohs(address.sin_port));

            //Close the socket and mark as 0 in list for reuse
            closesocket(s);
            client_socket[i] = 0;
          }
          else
          {
            printf("Recepting error, error code : %d", error_code);
          }
        }
        if (valread == 0)
        {
          //Somebody disconnected , get his details and print
          printf("Disconnected client - ip : %s , port : %d \n", inet_ntoa(address.sin_addr), ntohs(address.sin_port));

          //Close the socket and mark as 0 in list for reuse
          closesocket(s);
          client_socket[i] = 0;
        }

        //Echo back the message that came in
        else
        {
          //add null character, if you want to use with printf/puts or other string handling functions
          if (strcmp(buffer, "S") != 0)
          {
            buffer[valread] = '\0';
            printf("%s:%d - %s \n", inet_ntoa(address.sin_addr), ntohs(address.sin_port), buffer);
            send(s, buffer, valread, 0);
          }
        }
      }
    }
  }

  closesocket(s);
  WSACleanup();

  return 0;
}
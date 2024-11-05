//============================================================================
// Name        : server.c
// Author      : Silver Moon
// Edited by   : Bruno P. Santos
// Copyright   :
// Description : Server to handle a connection C, Ansi-style
//============================================================================

#include <arpa/inet.h>  //inet_addr
#include <stdio.h>
#include <stdlib.h>     // atoi
#include <string.h>     // strlen
#include <sys/socket.h>
#include <unistd.h>     // write

int main(int argc, char* argv[]) {
    int socket_desc, client_sock, c, read_size;
    struct sockaddr_in server, client;
    char client_message[2000];

    // Check for required arguments
    if (argc != 3) {
        printf("Usage: %s <IP address> <Port>\n", argv[0]);
        return 1;
    }

    // Convert command-line arguments
    const char *ip_address = argv[1];
    int port = atoi(argv[2]);

    // Create socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1) {
        printf("Could not create socket\n");
        return 1;
    }
    puts("Socket created");

    // Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(ip_address);  // Use provided IP address
    server.sin_port = htons(port);                   // Use provided port

    // Bind
    if (bind(socket_desc, (struct sockaddr*)&server, sizeof(server)) < 0) {
        perror("Bind failed. Error");
        return 1;
    }
    puts("Bind done");

    // Listen
    listen(socket_desc, 1);

    // Accept an incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);

    // Accept connection from an incoming client
    client_sock = accept(socket_desc, (struct sockaddr*)&client, (socklen_t*)&c);
    if (client_sock < 0) {
        perror("Accept failed");
        return 1;
    }
    puts("Connection accepted");

    // Receive a message from client
    while ((read_size = recv(client_sock, client_message, 2000, 0)) > 0) {
        // Send the message back to client
        write(client_sock, client_message, strlen(client_message));
    }

    if (read_size == 0) {
        puts("Client disconnected");
        fflush(stdout);
    } else if (read_size == -1) {
        perror("Receive failed");
    }

    return 0;
}

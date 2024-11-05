//============================================================================
// Name        : client.c
// Author      : Silver Moon
// Edited by   : Bruno P. Santos
// Copyright   :
// Description : C ECHO client example using sockets, Ansi-style
//============================================================================

#include <arpa/inet.h>   // inet_addr
#include <stdio.h>       // printf
#include <stdlib.h>      // atoi
#include <string.h>      // strlen
#include <sys/socket.h>  // socket
#include <unistd.h>      // close

int main(int argc, char* argv[]) {
    int sock;
    struct sockaddr_in server;
    char message[1000], server_reply[2000];

    // Check for required arguments
    if (argc != 3) {
        printf("Usage: %s <IP address> <Port>\n", argv[0]);
        return 1;
    }

    // Convert command-line arguments
    const char *ip_address = argv[1];
    int port = atoi(argv[2]);

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        printf("Could not create socket\n");
        return 1;
    }
    puts("Socket created");

    server.sin_addr.s_addr = inet_addr(ip_address);  // Use provided IP address
    server.sin_family = AF_INET;
    server.sin_port = htons(port);                   // Use provided port

    // Connect to remote server
    if (connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0) {
        perror("Connect failed. Error");
        return 1;
    }

    puts("Connected\n");

    // Keep communicating with the server
    while (1) {
        printf("Enter message: ");
        scanf("%s", message);

        // Send data
        if (send(sock, message, strlen(message), 0) < 0) {
            puts("Send failed");
            return 1;
        }

        // Receive a reply from the server
        if (recv(sock, server_reply, 2000, 0) < 0) {
            puts("Receive failed");
            break;
        }

        printf("Server reply: ");
        puts(server_reply);
    }

    close(sock);
    return 0;
}
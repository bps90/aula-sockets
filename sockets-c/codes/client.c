//============================================================================
// Nome        : client.c
// Autor       : Silver Moon
// Editado por : Bruno P. Santos
// Copyright   :
// Descrição   : Cliente ECHO em C utilizando sockets, estilo Ansi
//============================================================================

#include <arpa/inet.h>   // Para inet_addr
#include <stdio.h>       // Para printf
#include <stdlib.h>      // Para atoi
#include <string.h>      // Para strlen
#include <sys/socket.h>  // Para socket
#include <unistd.h>      // Para close

int main(int argc, char* argv[]) {
    int sock;
    struct sockaddr_in server;
    char message[1000], server_reply[2000];

    // Verifica se os argumentos necessários foram passados
    if (argc != 3) {
        printf("Uso: %s <Endereço IP> <Porta>\n", argv[0]);
        return 1;
    }

    // Converte os argumentos da linha de comando
    const char *ip_address = argv[1];
    int port = atoi(argv[2]);

    // Cria o socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        printf("Não foi possível criar o socket\n");
        return 1;
    }
    puts("Socket criado");

    // Define as informações do servidor
    server.sin_addr.s_addr = inet_addr(ip_address);
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    // Conecta ao servidor remoto
    if (connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0) {
        perror("Falha na conexão");
        return 1;
    }

    puts("Conectado\n");

    // Mantém a comunicação com o servidor
    while (1) {
        printf("Digite a mensagem: ");
        fgets(message, sizeof(message), stdin);

        // Envia a mensagem
        if (send(sock, message, strlen(message), 0) < 0) {
            puts("Falha ao enviar");
            return 1;
        }

        // Recebe a resposta do servidor
        if (recv(sock, server_reply, 2000, 0) < 0) {
            puts("Falha ao receber a resposta");
            break;
        }

        printf("Resposta do servidor: %s\n", server_reply);

        // Limpa o buffer server_reply após imprimir a resposta
        memset(server_reply, 0, sizeof(server_reply));
    }

    // Fecha o socket
    close(sock);

    return 0;
}

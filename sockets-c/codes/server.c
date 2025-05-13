//============================================================================
// Nome        : server.c
// Autor       : Silver Moon
// Editado por : Bruno P. Santos
// Copyright   :
// Descrição   : Servidor para lidar com uma conexão em C, estilo Ansi
//============================================================================

#include <arpa/inet.h>  // Para inet_addr
#include <stdio.h>
#include <stdlib.h>     // Para atoi
#include <string.h>     // Para strlen
#include <sys/socket.h>
#include <unistd.h>     // Para write

int main(int argc, char* argv[]) {
    int socket_desc, client_sock, c, read_size;
    struct sockaddr_in server, client;
    char client_message[2000];

    // Verifica se os argumentos necessários foram passados
    if (argc != 3) {
        printf("Uso: %s <Endereço IP> <Porta>\n", argv[0]);
        return 1;
    }

    // Converte os argumentos da linha de comando
    const char *ip_address = argv[1];
    int port = atoi(argv[2]);

    // Cria o socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1) {
        printf("Não foi possível criar o socket\n");
        return 1;
    }
    puts("Socket criado");

    // Prepara a estrutura sockaddr_in
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(ip_address);
    server.sin_port = htons(port);

    // Realiza o bind (associa o socket ao IP e porta)
    if (bind(socket_desc, (struct sockaddr*)&server, sizeof(server)) < 0) {
        perror("Falha no bind. Erro");
        return 1;
    }
    puts("Bind realizado");

    // Define o socket para ouvir conexões
    listen(socket_desc, 1);

    // Aguarda por conexões
    puts("Aguardando conexões...");
    c = sizeof(struct sockaddr_in);

    // Aceita a conexão de um cliente
    client_sock = accept(socket_desc, (struct sockaddr*)&client, (socklen_t*)&c);
    if (client_sock < 0) {
        perror("Falha ao aceitar a conexão");
        return 1;
    }
    puts("Conexão aceita");

    // Recebe a mensagem do cliente
    while ((read_size = recv(client_sock, client_message, 2000, 0)) > 0) {
        // Adiciona o caractere nulo para finalizar a string
        client_message[read_size] = '\0';

        // Envia a mensagem de volta ao cliente
        write(client_sock, client_message, strlen(client_message));

        // Limpa o buffer após enviar a mensagem
        memset(client_message, 0, sizeof(client_message));
    }

    // Verifica se a conexão foi encerrada
    if (read_size == 0) {
        puts("Cliente desconectado");
        fflush(stdout);
    } else if (read_size == -1) {
        perror("Falha ao receber a mensagem");
    }

    return 0;
}

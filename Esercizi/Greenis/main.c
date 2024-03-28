#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "database.h"

#define PORT 7379
#define MAX_CONNECTIONS 10
#define MAX_BUFFER_SIZE 4096
#define MAX_SIZE 1024 
#define MESSAGE_OK "+OK\r\n"
#define MESSAGE_NOT_OK "$-1\r\n"

char strings[MAX_CONNECTIONS][MAX_BUFFER_SIZE];

void set_record(int client_socket,Node* database,char* key,char* value){
    Record * record = create_Record(key,value);
    set(database,record);
    ssize_t bytes_sent = send(client_socket, MESSAGE_OK, strlen(MESSAGE_OK), 0);
    if (bytes_sent < 0) {
        perror("send");
        close(client_socket);
        exit(EXIT_FAILURE);
    }
}

void handle_client(int client_socket,Node* database) {
    char buffer[MAX_BUFFER_SIZE];
    char message_connection_client1[] = "*4\r\n$6\r\nCLIENT\r\n$7\r\nSETINFO\r\n$8\r\nLIB-NAME\r\n$8\r\nredis-py\r\n";
    char message_connection_client2[] = "*4\r\n$6\r\nCLIENT\r\n$7\r\nSETINFO\r\n$7\r\nLIB-VER\r\n$5\r\n5.0.3\r\n";
    ssize_t bytes_received;

    while (1){
        
        memset(buffer,0,MAX_BUFFER_SIZE);

        bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
        if (bytes_received < 0) {
            perror("recv");
            close(client_socket);
            exit(EXIT_FAILURE);
        }

        // Copy received string to strings array
        strncpy(strings[client_socket], buffer, sizeof(strings[client_socket]));
        
        //Setup connetion
        if(strcmp(strings[client_socket],message_connection_client1) == 0 ){
            ssize_t bytes_sent = send(client_socket, MESSAGE_OK, strlen(MESSAGE_OK), 0);
            continue;
            if (bytes_sent < 0) {
                perror("send");
                close(client_socket);
                exit(EXIT_FAILURE);
            }
        }
         if(strcmp(strings[client_socket],message_connection_client2) == 0 ){
            ssize_t bytes_sent = send(client_socket, MESSAGE_OK, strlen(MESSAGE_OK), 0);
            continue;
            if (bytes_sent < 0) {
                perror("send");
                close(client_socket);
                exit(EXIT_FAILURE);
            }
        }
        
       //Tokenizzazione
        int i = 0;
        char  tokens[MAX_SIZE][MAX_BUFFER_SIZE];
        char *token = strtok(buffer, "\r\n");

        for (int i = 0; i < MAX_SIZE; i++)
        {
            memset(tokens[i],0,MAX_BUFFER_SIZE);
        }
        while (token != NULL) {
            strcpy(tokens[i++],token);
            token = strtok(NULL, "\r\n");
        }
        //for (int j = 0; j < i; j++) { printf("Token %d: %s\n", j, tokens[j]); }

        //Parsing SET
        if(strcmp(tokens[2],"SET") == 0 ){
            char* key = tokens[4];
            char* value = tokens[6]; 
            set_record(client_socket,database,key,value);
        }

        //Parsing GET

        
        //printf("Received string from client %d: %s", client_socket, strings[client_socket]);
    }


    close(client_socket);
    exit(EXIT_SUCCESS);
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    pid_t child_pid;

 
    Node* database = create_Node(NULL);

  
    // Create server socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Initialize server address structure
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORT);

    // Bind server socket to the specified address and port
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_socket, MAX_CONNECTIONS) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    while (1) {
        // Accept incoming connection
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);
        if (client_socket < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        // Fork a child process to handle the client
        child_pid = fork();
        if (child_pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (child_pid == 0) {
            // Child process
            handle_client(client_socket,database);
        } else {
            // Parent process
            
             // Close client socket in parent process
        }
    }

    return 0;
}

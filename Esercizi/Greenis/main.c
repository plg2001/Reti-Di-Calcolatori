#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 7379
#define MAX_CONNECTIONS 10
#define MAX_BUFFER_SIZE 8192

char strings[MAX_CONNECTIONS][MAX_BUFFER_SIZE];

void handle_client(int client_socket) {
    char buffer[MAX_BUFFER_SIZE];
    ssize_t bytes_received;

    bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
    if (bytes_received < 0) {
        perror("recv");
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    // Copy received string to strings array
    strncpy(strings[client_socket], buffer, sizeof(strings[client_socket]));

    printf("Received string from client %d: %s", client_socket, strings[client_socket]);

    const char *response = "+OK\r\n";
    ssize_t bytes_sent = send(client_socket, response, strlen(response), 0);
    if (bytes_sent < 0) {
        perror("send");
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    close(client_socket);
    exit(EXIT_SUCCESS);
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    pid_t child_pid;

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
             // Close server socket in child process
            handle_client(client_socket);
        } else {
            // Parent process
            
             // Close client socket in parent process
        }
    }

    return 0;
}

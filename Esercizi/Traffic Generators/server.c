#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/select.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024
#define PORT 8080

typedef struct {
    int rand;
}Packet;

int main(){

    int server_socket;
    struct sockaddr_in server_addr,client_addr;
    char buffer[BUFFER_SIZE];

    Packet packet;
    packet.rand = 0;
    if((server_socket = socket(AF_INET,SOCK_DGRAM,0)) == -1){
        perror("Errore Creazione socket");
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORT);

    if((bind(server_socket,(struct sockaddr*) &server_addr,sizeof(server_addr))) == -1){
        perror("Errore nella Bind");
    }

    printf("Server avviato. In ascolto sulla porta %d\n", PORT);


    socklen_t addr_len = sizeof(client_addr);
    int recv_len = recvfrom(server_socket, &packet, BUFFER_SIZE, 0, (struct sockaddr*)&client_addr, &addr_len);
    if (recv_len == -1) {
        perror("Errore nella ricezione dei dati");
        exit(EXIT_FAILURE);
    }
    printf("Dio Cantante : %d",packet.rand);
    

    
    
}


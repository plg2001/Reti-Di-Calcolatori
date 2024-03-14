#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/select.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1" // Indirizzo IP del server (localhost)
#define PORT 8080
#define BUFFER_SIZE 1024

typedef struct {
  
    int rand;
}Packet;


int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    Packet pack;

    pack.rand = 1002;
    
    // Creazione del socket
    if ((client_socket = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("Errore nella creazione del socket");
        exit(EXIT_FAILURE);
    }
    
    // Inizializzazione della struttura del server
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    
    // Conversione dell'indirizzo IP del server da stringa a formato binario
    if (inet_aton(SERVER_IP, &server_addr.sin_addr) == 0) {
        perror("Errore nella conversione dell'indirizzo IP");
        exit(EXIT_FAILURE);
    }
    


    printf("%d",pack.rand);
       
    // Invio del messaggio al server
    if (sendto(client_socket, &pack, strlen(buffer), 0, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Errore nell'invio del messaggio al server");
        exit(EXIT_FAILURE);
    }

    printf("Messaggio inviato al server.\n");

    // Ricezione della risposta dal server

    // Chiusura del socket
    close(client_socket);
    
    return 0;
}

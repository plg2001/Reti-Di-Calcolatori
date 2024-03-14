#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <time.h>

#define PORT 8080

typedef struct {
    int rand;
}Packet;

Packet create_packet(){
    Packet ris;
    ris.rand = 13;
    
    return ris;
}

int main(int argc, char *argv[]){
    int socket_;
    struct sockaddr_in broadcast_addr;
    Packet packet = create_packet();

    if((socket_ = socket(AF_INET,SOCK_DGRAM,0)) == -1){
        perror("Errore Creazione socket");
    }
    
    memset(&broadcast_addr, 0, sizeof(broadcast_addr));
    broadcast_addr.sin_family = AF_INET;
    broadcast_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    broadcast_addr.sin_port = htons(PORT);

     if((bind(socket_,(struct sockaddr*) &broadcast_addr,sizeof(broadcast_addr))) == -1){
        perror("Errore nella Bind");
    }

    //Gestiso il leader
    if(strcmp(argv[1],"0") == 0){
        sleep(1);
                       
    }

}
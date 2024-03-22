#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <time.h>
#include <math.h>

#define PORT 9999
#define IP_FOUND "IP_FOUND"

typedef struct {
    int rand;
    int id_sender;
    //int id_recevier;
}Packet;



Packet create_packet(int id){
    Packet ris;
    ris.rand = rand(); 
    ris.id_sender = id;
    return ris;
}

int check_is_neighbor(int *neighbors,int k,int size_of_arr){
    for (int i = 0; i < size_of_arr; i++)
    {
        if (neighbors[i] == k)
        {
            return 1;
        }

    }

    return 0;
    
}

int main(int argc, char *argv[]){

    setvbuf(stdout, NULL, _IONBF, 0);

    int socket_;
    struct sockaddr_in node_addr, broadcast_addr;
    int id_nodo = atoi(argv[1]);
    int ret;
    int yes = 1;
    int addr_len;
    char buffer[1024];
  
    /*if (argc < 3) {
      
        perror("No neighbor for this node");
        return 1;
    }*/

    int * neighbors = calloc(sizeof(int), argc - 2);
    for (int i = 0; i < argc - 2; i ++) {
        neighbors[i] = atoi(argv[i + 2]);
    }

    if((socket_ = socket(AF_INET, SOCK_DGRAM, 0)) == -1){
        perror("Errore Creazione socket");
    }
    
    ret = setsockopt(socket_, SOL_SOCKET, SO_BROADCAST, (char*)&yes, sizeof(yes));
    if (ret == -1) {
        perror("setsockopt error");
        return 0;
    }
    

    ret = setsockopt(socket_, SOL_SOCKET, SO_REUSEADDR, (char*)&yes, sizeof(yes));
    if (ret == -1) {
        perror("setsockopt error");
        return 0;
    }

    addr_len = sizeof(struct sockaddr_in);

    memset((void*)&node_addr, 0, addr_len);
    node_addr.sin_family = AF_INET;
    node_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    node_addr.sin_port = htons(PORT);


    if (bind(socket_, (struct sockaddr *)&node_addr, addr_len) == -1) {
            perror("bind error");
            return 0;
    }

    memset((void*)&broadcast_addr, 0, addr_len);
    broadcast_addr.sin_family = AF_INET;
    broadcast_addr.sin_addr.s_addr = htonl(INADDR_BROADCAST);
    broadcast_addr.sin_port = htons(PORT);
   
    if (id_nodo == 0){
        while(1)
        {   
            sleep(1);
            Packet packet_to_send = create_packet(id_nodo);

            ret = sendto(socket_, &packet_to_send,sizeof(Packet), 0, (struct sockaddr*) &broadcast_addr, addr_len);
            if(ret == -1){
                perror("\nErrore nell'invio del messaggio al server");
                exit(EXIT_FAILURE);
            }
        }
        
      
    }

    else{
        while (1){

            printf("Nodo %d in attesa di ricezione messaggio\n",id_nodo);
            Packet packet_to_receive;
            ret = recvfrom(socket_,&packet_to_receive, sizeof(Packet), 0, (struct sockaddr*)&broadcast_addr, &addr_len);
            if(ret == -1){
                perror("Errore nella ricezione del messaggio\n");
                exit(EXIT_FAILURE);
            }

            if(check_is_neighbor(neighbors,packet_to_receive.id_sender,argc-2) == 1){
                printf("\n%d\n",packet_to_receive.rand);
            }

        }       
    }
   
}
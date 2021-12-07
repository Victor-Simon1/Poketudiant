#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include "client.h"
#include "error.h"

/*
    =======================   UDP   ================================
*/

ssize_t client_receive_udp(struct client *this,char* buf, size_t size){
    if(!buf) return 0;
    return recvfrom(this->socket, buf, size, 0, NULL, NULL);
}
void client_send_udp(struct client* this,char*msg){
    if(sendto(this->socket,msg,strlen(msg),0,(struct sockaddr*)&this->clientAddr,sizeof(struct sockaddr_in))==ERR)
        printf("err");
       // neterr_client(this,SEND_ERR);
}

Client client_create_udp(char* addr,int port){
    Client clt=malloc(sizeof(struct client));
    int sfd;
    if((sfd=socket(AF_INET,SOCK_DGRAM,0))==ERR){
       // neterr_client(clt,SOCKET_ERR);
    }

	int optval=1; /*Prepare the options of the socket for Broadcast */
 	int optlen=sizeof(int); 

	if(setsockopt(sfd,SOL_SOCKET,SO_BROADCAST,(char *) &optval,optlen)){ 
	    perror("Error setting socket to BROADCAST mode"); 
  	    exit(1); 
 	}
    memset(clt->buffer_send, 0, sizeof(char) * SIZE);
    memset(clt->buffer_recv, 0, sizeof(char) * SIZE);

    memset(&clt->clientAddr,0,sizeof(struct sockaddr_in));

    clt->socket=sfd;
    clt->clientAddr.sin_family=AF_INET;
    clt->clientAddr.sin_port=htons((uint16_t) port);
    clt->clientAddr.sin_addr.s_addr = htonl(INADDR_BROADCAST);

    clt->client_receive=&client_receive_udp;
    clt->client_send=&client_send_udp;

    //if(!inet_aton(addr,&clt->clientAddr.sin_addr)){ //neterr_client(clt,SOCKET_ERR);
   // }

    return clt;
}

void client_close_and_free(Client this){
    close(this->socket);
    free(this);
}


/*
    =======================   TCP   ================================
*/

static ssize_t client_receive_tcp(struct client*this,char* buf, size_t size){
    if(!buf) return 0;
    return recv(this->socket, buf, size, 0);
}

static void client_send_tcp(struct client* this,char*msg){
    if(send(this->socket,msg,strlen(msg),0)==ERR)
        printf("err");
        //neterr_client(this,SEND_ERR);

}

Client client_create_tcp(char* addr,int port){
    Client clt=malloc(sizeof(struct client));
    int sfd;
    if((sfd=socket(AF_INET,SOCK_STREAM,0))==ERR){
        //neterr_client(clt,SOCKET_ERR)
        printf("err sock");
    }

    memset(&clt->buffer_send, 0, sizeof(char) * SIZE);
    memset(&clt->buffer_recv, 0, sizeof(char) * SIZE);
    memset(&clt->clientAddr,0,sizeof(struct sockaddr_in));

    clt->socket=sfd;
    clt->clientAddr.sin_family=AF_INET;
    clt->clientAddr.sin_port=htons((uint16_t) port);
    clt->client_receive=&client_receive_tcp;
    clt->client_send=&client_send_tcp;
    clt->len = sizeof(struct sockaddr_in);
    if(!inet_aton(addr,&clt->clientAddr.sin_addr)){
         //neterr_client(clt,SOCKET_ERR);
         printf("ef,oen");
    }
    return clt;
}


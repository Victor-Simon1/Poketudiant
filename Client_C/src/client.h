#ifndef CLIENT_H
#define CLIENT_H


#include <zconf.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define ERR -1
#define SIZE 500


typedef struct client{
    int socket;
    struct sockaddr_in clientAddr;
    socklen_t len;
    char buffer_send[SIZE];
    char buffer_recv[SIZE];
    ssize_t (*client_receive)(struct client* this,char*buf,size_t size);
    void (*client_send)(struct client* this,char*msg);
}*Client;


Client clientUDP;
Client clientTCP;


// UDP
ssize_t client_receive_udp(struct client *this,char* buf, size_t size);
void client_send_udp(struct client* this,char*msg);
Client client_create_udp(char* addr,int port);

// TCP
static ssize_t client_receive_tcp(struct client*this,char* buf, size_t size);
static void client_send_tcp(struct client* this,char*msg);
Client client_create_tcp(char* addr,int port);

void client_close_and_free(Client this);


void update();
void refreshGame();

#endif 











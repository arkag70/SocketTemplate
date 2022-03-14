#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#define PORT 8080
#define QUEUE_LEN 3
#define BUFFER_SIZE 1024

class Server{
    
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt;
    int addrlen;
    char buffer[BUFFER_SIZE];
    char *ack;
    bool setup_server;

public:
       
    Server();
    void read_data();
};
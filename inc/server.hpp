#ifndef _SERVER_HPP_
#define _SERVER_HPP_

#include <unistd.h>
#include <iostream>
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
    char *ack;
    bool setup_server;
    int code;
    uint64_t payload_size;
    char buffer[BUFFER_SIZE];
    int bytes;

public:
       
    Server();
    void read_data(uint8_t *data, uint64_t size);
    void send_ack();
    ~Server();
};

#endif
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
#include <vector>
#define PORT 8000
#define QUEUE_LEN 3
#define BUFFER_SIZE 1024
#define SIZEARRAY 8
#define MAX_RETRIES 10

class Server{
    
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt;
    int addrlen;
    char *ack;
    bool setup_server;
    uint64_t size;
    uint8_t *data;

public:
       
    Server();
    void send_data(uint8_t *buf, uint64_t size);
    void read_data(uint8_t *data);
    bool read_data(std::vector<uint8_t> &data);
    ~Server();
};

#endif
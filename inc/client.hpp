#ifndef _CLIENT_HPP_
#define _CLIENT_HPP_

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <vector>
#define PORT 8080
#define BUFFER_SIZE 1024
#define SIZEARRAY 8

class Client{
    int sock, valread;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE];
    bool setup_client;
    std::vector<uint8_t> gateway_wrapper;
    uint8_t size_array[SIZEARRAY];

public:
    Client();
    void connect_to_server();
    void send_data(uint8_t *buf, uint64_t size, uint8_t code);
    void read_data();
    void close_connection();
};

#endif
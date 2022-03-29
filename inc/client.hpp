#ifndef _CLIENT_HPP_
#define _CLIENT_HPP_

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <vector>
#define PORT 8080
#define HOME_IP "127.0.0.1"
#define BUFFER_SIZE 1024
#define SIZEARRAY 8

class Client{
private:
    int sock, valread;
    struct sockaddr_in serv_addr;
    bool setup_client;
    uint32_t port;
    std::string ip;
    uint64_t size;

public:
    Client(std::string ip = HOME_IP, uint32_t port = PORT);
    void connect_to_server();
    bool send_data(uint8_t *buf, uint64_t size);
    bool read_data(uint8_t *data);
    bool read_data(std::vector<uint8_t> &data);
    ~Client();
};

#endif
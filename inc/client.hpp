#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#define PORT 8080
#define BUFFER_SIZE 1024

class Client{
    int sock, valread;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE];
    bool setup_client;

public:
    Client();
    void connect_to_server();
    void send_data(char *buf, uint64_t size);
    void read_data();
    void close_connection();
};
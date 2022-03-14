#include "client.hpp"
#include <iostream>

Client::Client(): sock{}, setup_client{false}{
    memset(buffer, 0, BUFFER_SIZE);

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        std::cout << "Socket creation error \n";
    }
    else{
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(PORT);
        
        // Convert IPv4 and IPv6 addresses from text to binary form
        if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) 
        {
            std::cout << "\nInvalid address/ Address not supported \n";
        }
        else{

        }
    }
}

void Client::connect_to_server(){
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("Connection Failed: ");
    }
}

void Client::send_data(char *buf, uint64_t size){
    send(sock , buf , size , 0 );
    std::cout << "Client : " << buf << std::endl;
}

void Client::read_data(){
    valread = read( sock , buffer, BUFFER_SIZE);
    std::cout << "Server : " << buffer << std::endl;
}

void Client::close_connection(){
    if( close(sock) == -1){
        perror("Socket close error : ");
    }
}
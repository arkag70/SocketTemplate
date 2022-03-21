#include "client.hpp"
#include <iostream>

Client::Client(std::string ip, uint32_t port): sock{}, setup_client{false}, ip{ip}, port{port}{

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        std::cout << "Socket creation error \n";
    }
    else{
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(port);
        
        // Convert IPv4 and IPv6 addresses from text to binary form
        if(inet_pton(AF_INET, ip.c_str(), &serv_addr.sin_addr) <= 0) 
        {
            std::cout << "\nInvalid address/ Address not supported \n";
        }
        else{
            if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
            {
                perror("Connection Failed: ");
            }
        }
    }
}

void Client::send_data(uint8_t *data, uint64_t size){
    
    uint64_t leftover{size};
    uint64_t transported{};
    uint64_t chunk_size{};

    while(leftover > 0){
    
        if(leftover > BUFFER_SIZE){
            chunk_size = BUFFER_SIZE;
        }
        else{
            chunk_size = leftover;
        }
        write(sock, data + transported, chunk_size);
        transported += chunk_size;
        leftover = size - transported;
    }
}

void Client::read_data(uint8_t *data, uint64_t size){

    uint64_t transported{};
    uint64_t leftover{size};
    uint64_t chunk_size{};
    memset(data, 0, size);

    while(leftover > 0){
        
        if(leftover > BUFFER_SIZE){
            chunk_size = BUFFER_SIZE;
        }
        else{
            chunk_size = leftover;
        }
        read(sock, data + transported, chunk_size);
        transported += chunk_size;
        leftover = size - transported;
    }   
}

void Client::close_connection(){
    if( close(sock) == -1){
        perror("Socket close error : ");
    }
}
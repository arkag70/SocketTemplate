#include "client.hpp"
#include <iostream>

Client::Client(std::string ip, uint32_t port): sock{}, setup_client{false}, ip{ip}, port{port}, size{}{

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
    //first batch sends size
    write(sock, &size, SIZEARRAY);

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

bool Client::read_data(uint8_t *data){

    uint64_t size{};
    uint64_t bytes_read = read(sock, &size, SIZEARRAY);
    
    if(bytes_read < SIZEARRAY){
        std::cout << "Size of buffer not read properly\n";
        return false;
    }
    else{
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
            bytes_read = read(sock, data + transported, chunk_size);
            transported += bytes_read;
            leftover = size - transported;
        }
        return true;
    }     
}

bool Client::read_data(std::vector<uint8_t> &data){
    
    int bytes_read = read(sock, &size, SIZEARRAY);

    if(bytes_read != SIZEARRAY){
        std::cout << "Size not read correctly\n";
        return false;
    }
    else{
        data.resize(size, 0);
        
        uint64_t transported{};
        uint64_t leftover{size};
        uint64_t chunk_size{};
        int count{};
        while(leftover > 0){
            if(leftover > BUFFER_SIZE){
                chunk_size = BUFFER_SIZE;
            }
            else{
                chunk_size = leftover;
            }
            bytes_read = read(sock, &data[0] + transported, chunk_size);
            transported += bytes_read;
            leftover = size - transported;
        }
        return true;
    }
}

void Client::close_connection(){
    if( close(sock) == -1){
        perror("Socket close error : ");
    }
}
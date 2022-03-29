#include "server.hpp"


Server::Server():opt{1}, addrlen{sizeof(address)}, ack{"received at server"}, 
                setup_server{false}, size{}, data{nullptr}{

    // Creating socket file descriptor
    if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0){
        std::cout << "socket creation failed\n";
    }
    else{
        
        // Forcefully attaching socket to the port 8000
        if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))){
            std::cout << "setsockopt failure\n";
        }
        else{
            address.sin_family = AF_INET;
            address.sin_addr.s_addr = INADDR_ANY;
            address.sin_port = htons( PORT );

            // Forcefully attaching socket to the port 8000
            if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0){
                std::cout << "bind failed\n";
            }
            else{
                std::cout << "Server is Listening\n";
                if (listen(server_fd, QUEUE_LEN) < 0)
                {
                    perror("listen failed : ");
                }
                else{
                    std::cout << "Waiting for connections...\n";
                    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0){
                        std::cout << "accept error\n";
                    }
                    else{
                        char host[NI_MAXHOST];
                        char service[NI_MAXSERV];
                        memset(host, 0, NI_MAXHOST);
                        memset(service, 0, NI_MAXSERV);

                        if(getnameinfo((sockaddr*)&address, sizeof(address), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0){
                            std::cout << host << " connected on port " << service << std::endl;
                        }
                        else{
                            inet_ntop(AF_INET, &address.sin_addr, host, NI_MAXHOST);
                            std::cout << host << " connected on port " << ntohs(address.sin_port) << std::endl;
                        }
                        close(server_fd);
                        setup_server = true;
                    }
                }
            }
        }
    }
}

void Server::read_data(uint8_t *data){

    uint64_t size{};
    read(new_socket, &size, SIZEARRAY);
    
    uint64_t transported{};
    uint64_t leftover{size};
    uint64_t chunk_size{};
    memset(data, 0, size);
    //first data sent is size

    while(leftover > 0){
        
        if(leftover > BUFFER_SIZE){
            chunk_size = BUFFER_SIZE;
        }
        else{
            chunk_size = leftover;
        }
        read(new_socket, data + transported, chunk_size);
        transported += chunk_size;
        leftover = size - transported;
    }   
}

bool Server::read_data(std::vector<uint8_t> &data){
    
    int bytes_read = read(new_socket, &size, SIZEARRAY);

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
            bytes_read = read(new_socket, &data[0] + transported, chunk_size);
            transported += bytes_read;
            leftover = size - transported;
            std::cout << "Received : " << transported << " / " << size << " bytes\n";
        }
        return true;
    }
}

void Server::send_data(uint8_t *data, uint64_t size){
    
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
        write(new_socket, data + transported, chunk_size);
        transported += chunk_size;
        leftover = size - transported;
    }
}

Server::~Server(){

    close(new_socket);
}

#include "server.hpp"


Server::Server():opt{1}, addrlen{sizeof(address)}, ack{"received at server"}, 
                setup_server{false}, code{}, payload_size{}, bytes{}{
    memset(buffer, 0, BUFFER_SIZE);

    // Creating socket file descriptor
    if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0){
        std::cout << "socket creation failed\n";
    }
    else{
        
        // Forcefully attaching socket to the port 8080
        if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))){
            std::cout << "setsockopt failure\n";
        }
        else{
            address.sin_family = AF_INET;
            address.sin_addr.s_addr = INADDR_ANY;
            address.sin_port = htons( PORT );

            // Forcefully attaching socket to the port 8080
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

void Server::read_data(uint8_t *data, uint64_t size){

        memset(buffer, 0 , BUFFER_SIZE);
        bytes = 0;
        
        bytes = read(new_socket, buffer, size);
        if(bytes == -1){
            perror("recv error : ");
            close(new_socket);
        }
        else if(bytes == 0){
            std::cout << "read error : client disconnected\n";
            close(new_socket);
        }
        else if(bytes == size){
            memcpy(data, buffer, size);
        }
        
        // std::cout << "Client : " << std::string(buffer, 0, payload_size) << std::endl;

}

void Server::send_ack(){

    send(new_socket, ack, strlen(ack), 0);
}

Server::~Server(){
    close(new_socket);
}

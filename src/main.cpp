#include <iostream>
#include "server.hpp"
#include "client.hpp"
#include <string>
#include <sstream>

char payload[] = {"CSK KKR DC RCB"};

int main(int argc, char *argv[]){

    if(argc < 2){
        std::cout << "Error : No input parameters. (0 : Server, 1 : Client)\n";
    }
    else{
        std::stringstream args;
        for(int i=0; i<argc; ++i){
            args << argv[i] << " ";
        }
        std::string app_name{};
        int role{};
        int num_of_messages{};
        args >> app_name >> role >> num_of_messages;
        if(role == 0){
            Server server;
            server.read_data();
        }
        else if(role == 1){
            Client client;
            client.connect_to_server();
            for(int i = 0; i<num_of_messages; ++i){
                //client stream data to server
                client.send_data(payload, strlen(payload));
                client.read_data();
                usleep(1000 * 1000);
            }
            client.close_connection();
            
        }
    }

    return 0;
}
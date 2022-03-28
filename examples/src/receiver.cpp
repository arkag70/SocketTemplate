#include "receiver.hpp"
#include <vector>
#include <fstream>

Player::Player(){

    srand(time(0));
    id = 0;//rand() % (INT16_MAX - 1) + 1;
    strcpy(name, "arka");
    strcpy(location,maps[0].c_str());
    health = 100.0;
    strcpy(primary_weapon,weapons[0].c_str());
    strcpy(secondary_weapon,weapons[5].c_str());
}

int Player::get_id(){
    return id;
}

float Player::get_health(){
    return health;
}

const char* Player::get_location(){
    return location;
}

const char* Player::get_name(){
    return name;
}

const char* Player::get_primary_weapon(){
    return primary_weapon;
}

const char* Player::get_secondary_weapon(){
    return secondary_weapon;
}

std::ostream& operator<<(std::ostream &os, Player &p){
    os << "[" << p.get_id() << "] " 
    << "\nhealth : " << p.get_health() << " / 100\n"
    << p.get_name()
    << "\nPrimary : " << p.get_primary_weapon() 
    << "\nSecondary : " << p.get_secondary_weapon() 
    << "\nlocation : " << p.get_location() << "\n\n";
    
    return os;
}

void receive_simulated_data(){

    Player p;
    Server server;

    while(true){
        
        server.read_data((uint8_t *)&p);
        if(p.get_id() != 0)
            std::cout << "Server received : \n" << p;  
    }
    std::cout << "Simulated data received \n";
}

void receive_file(std::string file_name){

    Server server;
    
    std::vector<uint8_t> data;
    bool read_status = server.read_data(data);
    if(read_status){
        std::cout << "Received " << data.size() << " bytes\n";
        std::ofstream fout{file_name, std::ios::binary | std::ios::out};
        if(fout){
            
            for(auto const &byt : data){
                fout << byt;
            }
            fout.close();
            std::cout << "File received successfully\n";
        }
    }
    else{
        std::cout << "Receive error\n";
    }
}

int main(){

    std::cout << "Waiting to receive data... Starting server\n";

    // receive_simulated_data();
    receive_file("/home/gho1kor/arka/cpp_projects/ethcom/examples/data/img.jpg");

    return 0;
}
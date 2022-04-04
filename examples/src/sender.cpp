#include "sender.hpp"
#include <fstream>
#include <sstream>


Player::Player(){

    srand(time(0));
    id = 0;//rand() % (INT16_MAX - 1) + 1;
    // std::string n{"arka"};
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

void simulate(){
    
    uint64_t cycle{};
    Client client(ip, port);
    Player p;
    uint64_t size = sizeof(p);
    std::cout << "Size of data per cycle : " << size << "\n";

    while(true){
        usleep(1000 * 1000);
        cycle++;
        
        p.health += (rand() % 3) - 1;
        if (p.health > 100)
            p.health = 100;
        p.id++;
        strcpy(p.secondary_weapon,weapons[rand() % WEAPON_N].c_str());
        strcpy(p.primary_weapon, weapons[rand() % WEAPON_N].c_str());
        strcpy(p.location, maps[rand() % MAP_N].c_str());
        std::cout << "Client sent: \n" << p;
        client.send_data((uint8_t *)&p, size);

    }
}


void send_file(std::string ip = "localhost", uint32_t port = 8000 , std::string file_name = ""){

    std::fstream fin{file_name, std::ios::in | std::ios::binary};
    std::vector<uint8_t> buffer;
    if(fin){
        uint8_t byte{};
        while(fin >> std::noskipws >> byte){
            buffer.push_back(byte);
        }
        fin.close();
    }
    else{
        perror("Error");
        std::cout << "File couldn't be opened\n";
        return;
    }
    std::cout << "Size of file : " << buffer.size() << " bytes.\n";
    Client client(ip, port);
    bool send_status = client.send_data(buffer.data(), buffer.size());
    if(send_status == true){
        std::cout << "File sent successfully\n";
    }
    else{
        std::cout << "Error sending file\n";
    }
}


int main(int argc, char *argv[]){

    if(argc < 4){
        std::cout << " Error : Insufficient arguments\n";
        return 0;
    }
    std::stringstream ss{};
    for(int i=0; i<argc; ++i){
        ss << argv[i] << " ";
    }
    std::string runnable{};
    std::string host_ip{};
    uint32_t port{};
    std::string file_name{};

    ss >> runnable >> host_ip >> port >> file_name;
    send_file(ip, port, file_name);
    

    return 0;
}
#include "sender.hpp"

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

void simulate(){
    
    uint64_t cycle{};
    Client client(ip, port);
    Player p;
    uint64_t size = sizeof(p);

    while(true){
        usleep(1000 * 100);
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





int main(){

    simulate();
    

    return 0;
}
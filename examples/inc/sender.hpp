#ifndef _SENDER_HPP_
#define _SENDER_HPP_

#include <iostream>
#include <client.hpp>
#include <ctime>
#include <cstdlib>
#include <string>

const std::string ip = "172.30.1.4";
const uint32_t port{8080};

std::string maps[] = {
    "pier", "sanitarium", "black-market", "practice-range", "sakura", "nuclear-reactor"
};

std::string weapons[] = {
    "long-range-assult-rifle", "mid-range-assault-rifle", "shot-gun", "pistol", "sniper-rifle", "knives"
};

class __attribute__((__packed__)) Player{
    int id;
    float health;
    char name[24];
    char location[24];
    char primary_weapon[28];
    char secondary_weapon[28];
    friend void simulate();
    friend std::ostream& operator<<(std::ostream &os, Player &p);

public:
    Player();
    int get_id();
    const char* get_location();
    const char* get_name();
    float get_health();
    const char* get_primary_weapon();
    const char* get_secondary_weapon();
};

#define MAP_N sizeof(maps)/sizeof(maps[0])
#define WEAPON_N (sizeof(weapons)/sizeof(weapons[0]))

#endif
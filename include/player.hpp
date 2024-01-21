#pragma once
#include "unit.hpp"
#include <string>

class Level;
class Player : public Unit
{
public:
    Player();
    Player(int x, int y, std::string img_path);
    Player &operator=(const Player &other);


    void move(int dx, int dy);
    //player in this level
    Level * in_level = nullptr;
};

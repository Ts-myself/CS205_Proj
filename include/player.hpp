#pragma once
#include "unit.hpp"
#include <string>

class Level;
class Player : public Unit
{
public:
    Player();
    Player(int x, int y, std::string img_path);

    void move(int dx, int dy);
    //player in this level
    std::unique_ptr<Level> father_level = nullptr;

};

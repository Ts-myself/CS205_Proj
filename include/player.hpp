#pragma once
#include "unit.hpp"
#include <string>


class Player : public Unit
{
public:
    Player();
    Player(int x, int y, std::string img_path);

    void move(int dx, int dy);

};

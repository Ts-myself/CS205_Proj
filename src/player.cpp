#include "../include/player.hpp"

Player::Player() : Unit(0, 0, 0, " "){};

Player::Player(int x, int y, std::string img_path) : Unit(x, y, 0, img_path){};

void Player::move(int dx, int dy)
{
    x += dx;
    y += dy;
}

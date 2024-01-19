#include "../include/player.hpp"

Player::Player() : Unit(0, 0, 0, " "){
    state = 0;
};

Player::Player(int x, int y, std::string img_path) : Unit(x, y, 0, img_path){
    state = 0;
};
void Player::move(int dx, int dy) {
    x += dx;
    y += dy;
}

Player &Player::operator=(const Player &other) {
    x = other.x;
    y = other.y;
    type = other.type;
    img_path = other.img_path;
    state = other.state;
    in_level = other.in_level;
    return *this;
}



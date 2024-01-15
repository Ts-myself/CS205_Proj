#include <utility>

#include "../include/box.hpp"

Box::Box() : Unit(0, 0, 5, " ") {};

Box::Box(int x, int y, std::string img_path) : Unit(x, y, 1, img_path) {};

Box::Box(const Box &other) : Unit(other.x, other.y, other.type, other.img_path) {
    internal_level = other.internal_level;
    upper_box = std::make_unique<Box>(*other.upper_box);
}

Box &Box::operator=(const Box &other) {
    x = other.x;
    y = other.y;
    type = other.type;
    img_path = other.img_path;
    internal_level = other.internal_level;
    upper_box = std::make_unique<Box>(*other.upper_box);
    return *this;
}

void Box::move(int dx, int dy) {
    x += dx;
    y += dy;
}
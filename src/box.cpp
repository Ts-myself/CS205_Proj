#include <utility>

#include "../include/box.hpp"

Box::Box() : Unit(0, 0, 5, " ") {
    state = 0;
};

Box::Box(int x, int y, std::string img_path) : Unit(x, y, 1, img_path) {
    state = 0;
}

Box::Box(const Box &other) : Unit(other.x, other.y, other.type, other.img_path) {
    internal_level = other.internal_level;
    upper_box = std::make_unique<Box>(*other.upper_box);
    state = other.state;
}

Box::Box(int x, int y, std::string img_path, Level *father_level) : Unit(x, y, 1, img_path) {
    state = 0;
    this->father_level = father_level;
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
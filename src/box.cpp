#include <utility>

#include "../include/box.hpp"

Box::Box() : Unit(0, 0, 5, " ") {
    state = 0;
    position_to_enter[0] = 0;
    position_to_enter[1] = 0;
    is_has_internal_level = false;
};

Box::Box(int x, int y, std::string img_path) : Unit(x, y, 1, img_path) {
    state = 0;
    position_to_enter[0] = 0;
    position_to_enter[1] = 0;
    is_has_internal_level = false;
}

Box::Box(const Box &other) : Unit(other.x, other.y, other.type, other.img_path) {
    state = other.state;
    position_to_enter[0] = other.position_to_enter[0];
    position_to_enter[1] = other.position_to_enter[1];
    is_has_internal_level = other.is_has_internal_level;
    enter_direction = other.enter_direction;
    father_box = other.father_box;
    inter_level = other.inter_level;

}



Box &Box::operator=(const Box &other) {
    x = other.x;
    y = other.y;
    type = other.type;
    img_path = other.img_path;
    state = other.state;
    position_to_enter[0] = other.position_to_enter[0];
    position_to_enter[1] = other.position_to_enter[1];
    is_has_internal_level = other.is_has_internal_level;
    enter_direction = other.enter_direction;
    father_box = other.father_box;
    inter_level = other.inter_level;
    return *this;
}

void Box::move(int dx, int dy) {
    x += dx;
    y += dy;
}
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

Box::Box(int x, int y, std::string img_path, int enter_direction,
         int *position_to_enter, bool is_has_internal_level,
         Level *inter_level, Box *father_box) : Unit(x, y, 1, std::move(img_path)) {
    state = 0;
    this->position_to_enter[0] = position_to_enter[0];
    this->position_to_enter[1] = position_to_enter[1];
    this->is_has_internal_level = is_has_internal_level;
    this->enter_direction = enter_direction;
    this->inter_level = inter_level;
    this->father_box = father_box;
}

Box::Box(int x, int y, std::string img_path, int enter_direction, int *position_to_enter, bool is_has_internal_level,
         std::shared_ptr<Level> inter_level, std::shared_ptr<Box> father_box) : Unit(x, y, 1, std::move(img_path)) {
    state = 0;
    this->position_to_enter[0] = position_to_enter[0];
    this->position_to_enter[1] = position_to_enter[1];
    this->is_has_internal_level = is_has_internal_level;
    this->enter_direction = enter_direction;
    this->inter_level_ptr = inter_level;
    this->father_box_ptr = father_box;
}

void Box::set_num(int num) {
    box_num = num;
}

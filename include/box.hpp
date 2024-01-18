#pragma once

#include <string>
#include <memory>

#include "unit.hpp"
#include "map.hpp"

class Level;

class Box : public Unit {
public:
    Box();

    Box(int x, int y, std::string img_path);

    Box(const Box &other);



    void move(int dx, int dy);

    Box &operator=(const Box &other);

    bool is_has_internal_level;
    int enter_direction = 0; // 1: up, 2: down, 3: left, 4: right
    int position_to_enter[2]{};
    // box has this level
    std::shared_ptr<Level> inter_level = nullptr;
    // box in this box
    std::shared_ptr<Box> father_box = nullptr;
    // box in this level
    std::shared_ptr<Level> father_level = nullptr;
};
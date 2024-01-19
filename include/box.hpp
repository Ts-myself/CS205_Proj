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

    Box(int x, int y, std::string img_path, int enter_direction, int *position_to_enter,
        bool is_has_internal_level,
        Level *inter_level, Box *father_box);
    Box(int x, int y, std::string img_path, int enter_direction, int *position_to_enter,
        bool is_has_internal_level,
        std::shared_ptr<Level> inter_level, std::shared_ptr<Box> father_box);

    Box &operator=(const Box &other);


    void move(int dx, int dy);

    bool is_has_internal_level;
    int enter_direction = 0; // 1: up, 2: down, 3: left, 4: right
    int position_to_enter[2];
    // box has this level
    Level * inter_level = nullptr;
    std::shared_ptr<Level> inter_level_ptr = nullptr;
    // box in this box
    Box *father_box = nullptr;
    std::shared_ptr<Box> father_box_ptr = nullptr;
    // box in this level
    Level * father_level = nullptr;
    std::shared_ptr<Level> father_level_ptr = nullptr;
};
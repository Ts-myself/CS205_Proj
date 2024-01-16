#pragma once

#include <string>
#include <memory>

#include "unit.hpp"
#include "map.hpp"
#include "level.hpp"

class Box : public Unit {
public:
    Box();

    Box(int x, int y, std::string img_path);

    Box(const Box &other);

    Box(int x, int y, std::string img_path, Level *father_level);

    void move(int dx, int dy);

    Box &operator=(const Box &other);


    Level internal_level;
    bool is_has_internal_level = false;
    int enter_direction = 0; // 1: up, 2: down, 3: left, 4: right

    Level *father_level = nullptr;
    std::unique_ptr<Box> upper_box = nullptr;
    std::unique_ptr<Box> father_box = nullptr;
};
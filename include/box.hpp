#pragma once

#include <string>
#include <memory>

#include "level.hpp"
#include "unit.hpp"
#include "map.hpp"

class Box : public Unit {
public:
    Box();

    Box(int x, int y, std::string img_path);

    Box(const Box &other);

    void move(int dx, int dy);

    Box &operator=(const Box &other);


    Level internal_level;
    std::unique_ptr<Box> upper_box = nullptr;
    std::unique_ptr<Box> father_box = nullptr;
};
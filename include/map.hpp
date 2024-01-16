#pragma once

#include "unit.hpp"
#include <vector>
#include <string>

static constexpr int MAP_WIDTH = 31;
static constexpr int MAP_HEIGHT = 31;

class Map {
public:
    Map();

    Map(int width, int height);

    bool draw_map(std::string img_info);

    int width = MAP_WIDTH;
    int height = MAP_HEIGHT;
    Unit map_units[MAP_HEIGHT][MAP_WIDTH]; // from 1 to MAP_WIDTH-1, from 1 to MAP_HEIGHT-1
};
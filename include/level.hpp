#pragma once

#include "map.hpp"
#include "unit.hpp"
#include "player.hpp"
#include "box.hpp"

#include <vector>

class Level {
public:
    Level();

    Level(int level_number, Map &map, std::vector<Player> &players, std::vector<Box> &boxes);

    void print_level_CIL();

    bool player_movable(size_t player_index, int dx, int dy);

    int level_number = 1;
    Map map;
    std::vector<Player> players;
    std::vector<Box> boxes;
};
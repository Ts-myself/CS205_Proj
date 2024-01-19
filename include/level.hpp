#pragma once

#include "map.hpp"
#include "unit.hpp"
#include "player.hpp"
#include "box.hpp"

#include <vector>

class Level {
public:
    Level();

    Level(int level_number, Map &map, std::vector<Player*> &players, std::vector<Box*> &boxes);
    Level(int level_number, Map &map, std::vector<std::shared_ptr<Player>> &players, std::vector<std::shared_ptr<Box>> &boxes);

    void print_level_CIL();

//    int player_movable(size_t player_index, int dx, int dy);
//    void player_move(size_t player_index, int dx, int dy,int player_movable);

    int level_number = 1;
    Map map;
    std::vector<Player*> players;
    std::vector<std::shared_ptr<Player>> players_ptr;
    std::vector<Box*> boxes;
    std::vector<std::shared_ptr<Box>> boxes_ptr;
    void rew_state_Box();
    void rew_state_Player();
    void rew_state_All();
    bool is_win();
    Box *get_box(int x, int y);
    bool is_box(int x, int y);
    bool is_player(int x, int y);

    //level in this box
    Box * father_box = nullptr;
    std::shared_ptr<Box> father_box_ptr = nullptr;
    //outer level
    Level * father_level = nullptr;
    std::shared_ptr<Level> father_level_ptr = nullptr;
};
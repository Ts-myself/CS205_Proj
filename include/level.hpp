#pragma once

#include "map.hpp"
#include "unit.hpp"
#include "player.hpp"
#include "box.hpp"

#include <vector>

struct Point2 {
    int x;
    int y;
};

class Level {
public:
    Level();

    Level(int level_number, Map &map, std::vector<Player *> &players, std::vector<Box *> &boxes);

    void print_level_CIL();

    bool load_level(const std::string &level_path, std::vector<Level*> &internal_levels_, std::vector<Box*> &boxes_,
                    Player &player_, std::vector<std::string> &level_infos);
    bool load_level_by_info(const std::vector<std::string> &level_info, std::vector<Level *> &internal_levels_,
                    std::vector<Box *> &boxes_, Player &player_);

//    int player_movable(size_t player_index, int dx, int dy);
//    void player_move(size_t player_index, int dx, int dy,int player_movable);

    int level_number = 1;
    Map map;
    std::vector<Player *> players;

    std::vector<Box *> boxes;

    void rew_state_Box();

    void rew_state_Player();

    void rew_state_All();

    bool is_win();

    Box *get_box(int x, int y);
    bool is_box(int x, int y);
    bool is_player(int x, int y);

    //level in this box
    Box *father_box = nullptr;
    //outer level
    Level *father_level = nullptr;
};

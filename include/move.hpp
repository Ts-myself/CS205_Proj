//
// Created by 15093039942 on 2024/1/19.
//

#ifndef CS205_PROJ_MOVE_HPP
#define CS205_PROJ_MOVE_HPP
#include "level.hpp"
#include "player.hpp"
#include "box.hpp"
namespace move {
    void recurse_move(int dx, int dy, int x, int y, Box *box, Player *player, Level *level,int count);
    bool is_box(int x, int y, std::vector<Box> &boxes);
    bool is_player(int x, int y, std::vector<Player*> &players);
    bool is_can_enter(int dx, int dy, int direction);

} // move

#endif //CS205_PROJ_MOVE_HPP

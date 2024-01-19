//
// Created by 15093039942 on 2024/1/19.
//

#include "move.hpp"
#include <iostream>

namespace move {
    void recurse_move(int dx, int dy, int x, int y, Box *box, Player *player, Level *level, int count) {
        if (count > 10) {
            std::cout << " count > 10" << std::endl;
            return;
        }
        int next_x = x;
        int next_y = y;
        int num = -1;
        while (is_box(next_x, next_y, level->boxes) || is_player(next_x, next_y, level->players)) {
            next_x += dx;
            next_y += dy;
            num++;
        }
        int width = level->map.width;
        int height = level->map.height;
        if (level->level_number == 0) {
            std::cout << "enter the level 0" << std::endl;
            return;
        }
        if (box == nullptr && player == nullptr) {
            std::cout << "error: box and player are both nullptr" << std::endl;
            return;
        }
        if (box != nullptr && player != nullptr) {
            std::cout << "error: box and player are both not nullptr" << std::endl;
            return;
        }
        if (next_x < 0 || next_x > width || next_y < 0 || next_y > height) {
            int enter_x = level->father_box->x;
            int enter_y = level->father_box->y;
            if (box != nullptr) {
                box->x = enter_x;
                box->y = enter_y;
                level->father_level->boxes.push_back(box);
                level->boxes.erase(level->boxes.begin() + (box - level->boxes[0]));
            }
            if (player != nullptr) {
                level->players.erase(level->players.begin());
                level->father_level->players.push_back(player);
                player->in_level = level->father_level;
                player->x = enter_x;
                player->y = enter_y;
            }
            recurse_move(dx, dy, enter_x, enter_y, box, player, level->father_level, count + 1);
            return;
        }
        int next_type = level->map.map_units[next_y][next_x].type;
        if (next_type == 2) {
            next_x -= dx;
            next_y -= dy;
            int temp_x = next_x - dx;
            int temp_y = next_y - dy;
            for (int i = num; i > 0; i--) {
                Box *temp_box = level->get_box(next_x, next_y);
                if (temp_box == nullptr) continue;
                if (!temp_box->is_has_internal_level) {
                    temp_x -= dx;
                    temp_y -= dy;
                    next_x -= dx;
                    next_y -= dy;
                    continue;
                }
                if (!is_can_enter(dx, dy, temp_box->enter_direction)) {
                    temp_x -= dx;
                    temp_y -= dy;
                    next_x -= dx;
                    next_y -= dy;
                    continue;
                }
                Box *temp_box1 = nullptr;
                if (is_box(temp_x, temp_y, level->boxes)) {
                    Box *temp_box2 = level->get_box(temp_x, temp_y);
                    level->boxes.erase(level->boxes.begin() + get_box_index(temp_x, temp_y, level->boxes));
                    temp_box2->x = temp_box->position_to_enter[0] - dx;
                    temp_box2->y = temp_box->position_to_enter[1] - dy;
                    temp_box->inter_level->boxes.push_back(temp_box2);
                    temp_box1 = temp_box2;
                    player = nullptr;
                    std::vector<Unit *> units;
                    int temp_x_1 = x;
                    int temp_y_1 = y;
                    while (is_box(temp_x_1, temp_y_1, level->boxes) || is_player(temp_x_1, temp_y_1, level->players)) {
                        if (is_player(temp_x_1, temp_y_1, level->players)) {
                            units.push_back(level->players[0]);
                        } else {
                            units.push_back(level->get_box(temp_x_1, temp_y_1));
                        }
                        temp_x_1 += dx;
                        temp_y_1 += dy;
                    }
                    for (auto &unit: units) {
                        unit->move(dx, dy);
                    }
                } else {
                    level->players.erase(level->players.begin());
                    temp_box->inter_level->players.push_back(player);
                    player->in_level = temp_box->inter_level;
                    player->x = temp_box->position_to_enter[0] - dx;
                    player->y = temp_box->position_to_enter[1] - dy;
                }
                recurse_move(dx, dy, temp_box->position_to_enter[0] - dx,
                             temp_box->position_to_enter[1] - dy,
                             temp_box1, player, temp_box->inter_level, count + 1);
                return;
            }
            std::cout << "player can't move" << std::endl;
            return;
        }
        if (next_type == 6 || next_type == 5 || next_type == 4 || next_type == 3) {
            std::vector<Unit *> units;
            int temp_x = x;
            int temp_y = y;
            while (is_box(temp_x, temp_y, level->boxes) || is_player(temp_x, temp_y, level->players)) {
                if (is_player(temp_x, temp_y, level->players)) {
                    units.push_back(level->players[0]);
                } else {
                    units.push_back(level->get_box(temp_x, temp_y));
                }
                temp_x += dx;
                temp_y += dy;
            }
            for (auto &unit: units) {
                unit->move(dx, dy);
            }
            return;
        }
    }

    bool is_box(int x, int y, std::vector<Box*> &boxes) {
        for (auto &box: boxes) {
            if (box->x == x && box->y == y) {
                return true;
            }
        }
        return false;
    }
    int get_box_index(int x, int y, std::vector<Box*> &boxes) {
        for (int i = 0; i < boxes.size(); i++) {
            if (boxes[i]->x == x && boxes[i]->y == y) {
                return i;
            }
        }
        return -1;
    }

    bool is_player(int x, int y, std::vector<Player *> &players) {
        for (auto player: players) {
            if (player->x == x && player->y == y) {
                return true;
            }
        }
        return false;
    }

    bool is_can_enter(int dx, int dy, int direction) {
        if (dx == 0 && dy == 1 && direction == 1) {
            return true;
        }
        if (dx == 0 && dy == -1 && direction == 2) {
            return true;
        }
        if (dx == 1 && dy == 0 && direction == 3) {
            return true;
        }
        if (dx == -1 && dy == 0 && direction == 4) {
            return true;
        }
        return false;
    }
} // move
#include "../include/level.hpp"

#include <iostream>

Level::Level() {};

Level::Level(int level_number, Map &map, std::vector<Player> &players, std::vector<Box> &boxes) {
    this->level_number = level_number;
    this->map = map;
    this->players = players;
    this->boxes = boxes;
}

void Level::print_level_CIL() {
    char level_print_row[MAP_WIDTH + 1];
    char symbol[] = {'P', 'O', '#', '=', '=', '-', ' ', 'p', 'o'};
    // 'P'-Player, 'O'-Box, '#'-Wall, '='-player check point, '='-box check point, ' '-empty , 'p'-Player on target, 'o'-Box on target
    for (int i = 1; i <= map.height; i++) {
        // draw the map
        for (int j = 1; j <= map.width; j++) {
            level_print_row[j - 1] = symbol[map.map_units[i][j].type];
        }
        // draw the players and boxes
        for (const auto &player: players) {
            if (player.y != i) {
                continue;
            }
            if (map.map_units[player.x][player.y].type == 3) {
                level_print_row[player.x - 1] = symbol[7];
            } else {
                level_print_row[player.x - 1] = symbol[0];
            }
        }
        for (const auto &box: boxes) {
            if (box.y != i) {
                continue;
            }
            if (map.map_units[box.x][box.y].type == 4) {
                level_print_row[box.x - 1] = symbol[8];
            } else {
                level_print_row[box.x - 1] = symbol[1];
            }
        }
        // print the row
        for (int j = 0; j < map.width; j++) {
            std::cout << level_print_row[j] << " ";
        }
        switch (i) {
            case 1:
                std::cout << "| P: Player               |";
                break;
            case 2:
                std::cout << "| p: Player on checkpoint |";
                break;
            case 3:
                std::cout << "| O: Box with no internal |";
                break;
            case 4:
                std::cout << "| =: Checkpoint           |";
                break;
            case 5:
                std::cout << "| -: Storage Point        |";
                break;
            case 6:
                std::cout << "| #: Wall                 |";
                break;
            case 7:
                std::cout << "| o: Box on storage point |";
                break;
            case 8:
                std::cout << "|                         |";
                break;
            case 9:
                std::cout << "|  W/A/S/D: Move          |";
                break;
            case 10:
                std::cout << "|  Esc: Pause             |";
                break;
            case 11:
                std::cout << "|  Current Level: " << level_number << "       |";
                break;
            default:
                break;
        }
        std::cout << std::endl;
    }
    if (map.height < 11) {
        for (int i = map.height; i <= 11; i++) {
            for (int j = 0; j < map.width; j++) {
                std::cout << "  ";
            }
            switch (i) {
                case 1:
                    std::cout << "| P: Player               |";
                    break;
                case 2:
                    std::cout << "| p: Player on checkpoint |";
                    break;
                case 3:
                    std::cout << "| O: Box with no internal |";
                    break;
                case 4:
                    std::cout << "| =: Checkpoint           |";
                    break;
                case 5:
                    std::cout << "| -: Storage Point        |";
                    break;
                case 6:
                    std::cout << "| #: Wall                 |";
                    break;
                case 7:
                    std::cout << "| o: Box on storage point |";
                    break;
                case 8:
                    std::cout << "|                         |";
                    break;
                case 9:
                    std::cout << "|  W/A/S/D: Move          |";
                    break;
                case 10:
                    std::cout << "|  Esc: Pause             |";
                    break;
                case 11:
                    std::cout << "|  Current Level: " << level_number << "       |";
                    break;
            }
            std::cout << std::endl;
        }
    }
}
// 0: not movable, 1: movable, 2: movable and push box,
// 3 : out of internal level, 4+: enter internal level,value - 4 is which box is be entered
int Level::player_movable(size_t player_index, int dx, int dy) {
    int next_x = players[player_index].x + dx;
    int next_y = players[player_index].y + dy;
    //out of map in box
    if (next_x < 1 || next_x > map.width || next_y < 1 || next_y > map.height){
        return 3;
    }
    int next_type = map.map_units[next_y][next_x].type;
    if (next_type == 0 || next_type == 2) {
        return 0;
    }
    if (next_type == 6 || next_type == 5) {
        return 1;
    }
    if (next_type == 1){
        int num_box = 1;
        while (map.map_units[next_y][next_x].type == 1) {
            next_x += dx;
            next_y += dy;
            num_box++;
            if (next_x < 1 || next_x > map.width || next_y < 1) {
                break;
            }
        }
        //out of map in box
        if (next_x < 1 || next_x > map.width || next_y < 1 || next_y > map.height){
            return 3;
        }
        int temp_map_type = map.map_units[next_y][next_x].type;
        //move multiple boxes
        if (temp_map_type == 6) {
            return 2;
        }
        if (temp_map_type == 0 || temp_map_type == 2) {
            next_x -= dx;
            next_y -= dy;
            int temp_x = next_x - dx;
            int temp_y = next_y - dy;
            for (int i = num_box; i > 0; i--) {
                Box *temp_box = get_box(next_x, next_y);
                if (temp_box == nullptr) {
                    return 0;
                }
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
                return 4 + i;
            }
            return 0;
        }
    }
    return 0;

}

void Level::player_move(size_t player_index, int dx, int dy,int player_movable) {
    if (player_movable == 0) {
        std::cout << "player can't move" << std::endl;
        return;
    }
    if (player_movable == 1) {
        players[player_index].move(dx, dy);
        return;
    }
    if(player_movable == 2){
        int next_x = players[player_index].x + dx;
        int next_y = players[player_index].y + dy;
        players[player_index].move(dx, dy);
        while (map.map_units[next_y][next_x].type == 1) {
            Box *temp_box = get_box(next_x, next_y);
            if (temp_box == nullptr) {
                return;
            }
            temp_box->move(dx, dy);
            next_x += dx;
            next_y += dy;
        }
        return;
    }
    if (player_movable == 3){
        int next_x = players[player_index].x + dx;
        int next_y = players[player_index].y + dy;
        if (next_x < 1 || next_x > map.width || next_y < 1 || next_y > map.height){
            Player temp_player = players[player_index];
            father_box->father_level->players.push_back(temp_player);
            players.erase(players.begin() + player_index);
            temp_player.x = father_box->x+dx;
            temp_player.y = father_box->y+dy;
            temp_player.father_level = father_box->father_level;
            return;
        }
        while (map.map_units[next_y][next_x].type == 1) {
            Box *temp_box_1 = get_box(next_x, next_y);
            if (temp_box_1 == nullptr) {
                return;
            }
            temp_box_1->move(dx, dy);
            next_x += dx;
            next_y += dy;
            if (next_x < 1 || next_x > map.width || next_y < 1 || next_y > map.height){
                Box *temp_box = get_box(next_x-dx, next_y-dy);
                if (temp_box == nullptr) {
                    return;
                }
                boxes.erase(boxes.begin() + (temp_box - &boxes[0]));
                father_box->father_level->boxes.push_back(*temp_box);
                temp_box->x = father_box->x+dx;
                temp_box->y = father_box->y+dy;
                temp_box->father_level = father_box->father_level;
            }
        }
        players[player_index].move(dx, dy);

    }
    //todo:enter internal level ,value - 4 is which box is be entered,design the change of player and box
}

void Level::rew_state_Box() {
    for (auto &box: boxes) {
        if (map.map_units[box.y][box.x].type == 4) {
            box.state = 1;
        } else {
            box.state = 0;
        }
    }
}
void Level::rew_state_Player() {
    for (auto &player: players) {
        if (player.state >= 2) {
            continue;
        }
        if (map.map_units[player.y][player.x].type == 3) {
            player.state = 1;
        } else {
            player.state = 0;
        }
    }
}
void Level::rew_state_All() {
    rew_state_Box();
    rew_state_Player();
}

Box *Level::get_box(int x, int y) {
    for (auto &box: boxes) {
        if (box.x == x && box.y == y) {
            return &box;
        }
    }
    return nullptr;
}
bool Level::is_can_enter(int dx, int dy, int direction) {
    switch (direction) {
        case 1:
            if (dy==-1&&dx==0){
                return true;
            }
            break;
        case 2:
            if (dy==1&&dx==0){
                return true;
            }
            break;
        case 3:
            if (dy==0&&dx==-1){
                return true;
            }
            break;
        case 4:
            if (dy==0&&dx==1){
                return true;
            }
            break;
        default:return false;
    }
}
#include "../include/level.hpp"

#include <iostream>
#include <string>
#include <fstream>

Level::Level() {};

Level::Level(int level_number, Map &map, std::vector<Player> &players, std::vector<Box> &boxes) {
    this->level_number = level_number;
    this->map = map;
    this->players = players;
    this->boxes = boxes;
}

void Level::print_level_CIL() {
    char level_print_row[MAP_WIDTH + 1];
    char symbol[] = {'P', 'O', '#', '@', '=', '-', ' ', 'p', 'o'};
    // 'P'-Player, 'O'-Box, '#'-Wall, '@'-player check point, '='-box check point, ' '-empty , 'p'-Player on target, 'o'-Box on target
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
        int a;
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

void Level::load_level(const std::string &level_path) {
    std::ifstream level_file(level_path);
    if (!level_file.is_open()) {
        std::cout << "Error: the level file cannot be opened." << std::endl;
        return;
    }
    std::string line;
    std::vector<std::string> level_info;
    while (getline(level_file, line)) {
        level_info.push_back(line);
    }
    level_file.close();
    // the format of the level file is as follows:
    /* Levels:
     * 8 8 // origin width height
     * ########
     * #=---@-#
     * #-=----#
     * #------#
     * #------#
     * ####--##
     * ..#--#..
     * ..####..
     * 3 // internal level number
     * 0 // belong to nth box
     * 4 6 // width height
     * ######
     * #-=---
     * #-----
     * ######
     * 1
     * 3 4
     * ####
     * #--#
     * #--#
     * 3
     * 4 4
     * #--#
     * #--#
     * #--#
     * ####
     * Boxes:
     * 4 //number of boxes
     * 0 3 2 // in nth level, x, y
     * 0 6 2
     * 0 3 5
     * 1 4 2
     * Players:
     * 1 // number of player
     * 0 5 2 // in nth level, x, y
     */

    std::vector<Level *> levels_ptr;
    // map of origin level
    int origin_map_width = std::stoi(level_info[1].substr(0, level_info[1].find(' ')));
    int origin_map_height = std::stoi(level_info[1].substr(level_info[1].find(' ') + 1));
    Map origin_map(origin_map_width, origin_map_height);
    std::string origin_map_info;
    for (int i = 2; i < 2 + origin_map_height; i++) {
        origin_map_info += level_info[i];
    }
    origin_map.draw_map(origin_map_info);
    {
        map = origin_map;
        levels_ptr.push_back(this);
    }

    // internal levels
    int internal_level_number = std::stoi(level_info[2 + origin_map_height]);
    int offsetLine = 3 + origin_map_height;
    std::vector<int> level_belong_box;
    for (int i = 0; i < internal_level_number; i++) {
        int belong_box = std::stoi(level_info[offsetLine]);
        level_belong_box.push_back(belong_box);
        int internal_map_width = std::stoi(level_info[offsetLine + 1].substr(0, level_info[offsetLine + 1].find(' ')));
        int internal_map_height = std::stoi(
                level_info[offsetLine + 1].substr(level_info[offsetLine + 1].find(' ') + 1));
        Map internal_map(internal_map_width, internal_map_height);

        std::string internal_map_info;
        for (int j = 0; j < internal_map_height; j++) {
            internal_map_info += level_info[offsetLine + 2 + i];
        }
        internal_map.draw_map(internal_map_info);
        offsetLine += 2 + internal_map_height;
    }

    // boxes
    std::vector<Box> belong_boxes;
    offsetLine += 1; // offset "Boxes:"
    int boxes_num = std::stoi(level_info[offsetLine]);
    for (int i = 0; i < boxes_num; i++) {
        int be_in_level = std::stoi(level_info[offsetLine + 1].substr(0, level_info[offsetLine + 1].find(' ')));
        int box_x = std::stoi(level_info[offsetLine + 1].substr(level_info[offsetLine + 1].find(' ') + 1,
                                                                level_info[offsetLine + 1].rfind(' ') -
                                                                level_info[offsetLine + 1].find(' ') - 1));
        int box_y = std::stoi(level_info[offsetLine + 1].substr(level_info[offsetLine + 1].rfind(' ') + 1));
        Box box(box_x, box_y, " ");
        belong_boxes.push_back(box);
        //todo: box father_box
//        box.father_level = levels_ptr[be_in_level];
        levels_ptr[be_in_level]->boxes.push_back(box);
        offsetLine += 1;
    }

    // players
    offsetLine += 1; // offset "Players:"
    int players_num = std::stoi(level_info[offsetLine]);
    for (int i = 0; i < players_num; i++) {
        int be_in_level = std::stoi(level_info[offsetLine + 1].substr(0, level_info[offsetLine + 1].find(' ')));
        int player_x = std::stoi(level_info[offsetLine + 1].substr(level_info[offsetLine + 1].find(' ') + 1,
                                                                   level_info[offsetLine + 1].rfind(' ') -
                                                                   level_info[offsetLine + 1].find(' ') - 1));
        int player_y = std::stoi(level_info[offsetLine + 1].substr(level_info[offsetLine + 1].rfind(' ') + 1));
        Player player(player_x, player_y, " ");
        //todo: player where
        levels_ptr[be_in_level]->players.push_back(player);
        offsetLine += 1;
    }

    //internal level belong to box
    for (int i = 0; i < internal_level_number; i++) {
        int belong_box = level_belong_box[i];
        levels_ptr[i]->father_box = std::make_unique<Box>(belong_boxes[belong_box]);
        //todo: fix below
//        std::shared_ptr<Level> temp_level_ptr = std::make_shared<Level>(*levels_ptr[i]);
//        belong_boxes[belong_box].inter_level = std::make_shared<Level>(*levels_ptr[i]);
    }
};

// 0: not movable, 1: movable, 2: movable and push box,
// 3 : out of internal level, 4+: enter internal level,value - 4 is which box is be entered
int Level::player_movable(size_t player_index, int dx, int dy) {
    int next_x = players[player_index].x + dx;
    int next_y = players[player_index].y + dy;
    //out of map in box
    if (next_x < 1 || next_x > map.width || next_y < 1 || next_y > map.height) {
        return 3;
    }
    int next_type = map.map_units[next_y][next_x].type;
    if (is_box(next_x, next_y, boxes)) {
        next_type = 1;
    }
    if (next_type == 0 || next_type == 2) {
        return 0;
    }
    if (next_type == 6 || next_type == 5) {
        return 1;
    }
    if (next_type == 1) {
        int num_box = 0;
        while (is_box(next_x, next_y, boxes)) {
            next_x += dx;
            next_y += dy;
            num_box++;
            if (next_x < 1 || next_x > map.width || next_y < 1) {
                break;
            }
        }
        //out of map in box
        if (next_x < 1 || next_x > map.width || next_y < 1 || next_y > map.height) {
            return 3;
        }
        int temp_map_type = map.map_units[next_y][next_x].type;
        //move multiple boxes
        if (temp_map_type == 6 || temp_map_type == 5) {
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

void Level::player_move(size_t player_index, int dx, int dy, int player_movable) {
    if (player_movable == 0) {
        std::cout << "player can't move" << std::endl;
        return;
    }
    if (player_movable == 1) {
        players[player_index].move(dx, dy);
        return;
    }
    if (player_movable == 2) {
        int next_x = players[player_index].x + dx;
        int next_y = players[player_index].y + dy;
        players[player_index].move(dx, dy);
        std::vector<Box *> temp_boxes;
        while (is_box(next_x, next_y, boxes)) {
            Box *temp_box = get_box(next_x, next_y);
            if (temp_box == nullptr) {
                return;
            }
            temp_boxes.push_back(temp_box);
            next_x += dx;
            next_y += dy;
        }
        for (auto temp_box: temp_boxes) {
            temp_box->move(dx, dy);
        }
        return;
    }
    if (player_movable == 3) {
        int next_x = players[player_index].x + dx;
        int next_y = players[player_index].y + dy;
        if (next_x < 1 || next_x > map.width || next_y < 1 || next_y > map.height) {
            Player *temp_player = &players[player_index];
            players.erase(players.begin() + 0);
            temp_player->x = father_box->x + dx;
            temp_player->y = father_box->y + dy;
            father_box->father_level->players.push_back(*temp_player);
            return;
        }
        players[player_index].move(dx, dy);
        std::vector<Box *> temp_boxes;
        while (is_box(next_x, next_y, boxes)) {
            Box *temp_box_1 = get_box(next_x, next_y);
            if (temp_box_1 == nullptr) {
                return;
            }
            temp_boxes.push_back(temp_box_1);
            next_x += dx;
            next_y += dy;
            if (next_x < 1 || next_x > map.width || next_y < 1 || next_y > map.height) {
                Box *temp_box = get_box(next_x - dx, next_y - dy);
                if (temp_box == nullptr) {
                    return;
                }
                boxes.erase(boxes.begin() + (temp_box - &boxes[0]));
                father_box->inter_level->boxes.push_back(*temp_box);
                temp_box->x = father_box->x + dx;
                temp_box->y = father_box->y + dy;
                temp_box->father_box = father_box->father_box;
                break;
            }
        }
        for (auto temp_box: temp_boxes) {
            temp_box->move(dx, dy);
        }
    }
    if (player_movable >= 4) {
        int next_x = players[player_index].x;
        int next_y = players[player_index].y;
        for (size_t i = 0; i < player_movable - 4; i++) {
            next_x += dx;
            next_y += dy;
        }
        Box *temp_box = get_box(next_x, next_y);
        if (player_movable - 4 == 1) {
            Player *temp_player = &players[player_index];
            players.erase(players.begin() + player_index);
            temp_player->x = temp_box->position_to_enter[0];
            temp_player->y = temp_box->position_to_enter[1];
            temp_box->inter_level->players.push_back(*temp_player);
            return;
        }
        Box *temp_box_1 = get_box(next_x - dx, next_y - dy);
        if (temp_box_1 == nullptr) {
            return;
        }
        boxes.erase(boxes.begin() + (temp_box_1 - &boxes[0]));
        temp_box_1->x = temp_box->position_to_enter[0];
        temp_box_1->y = temp_box->position_to_enter[1];
        temp_box_1->father_box = std::make_shared<Box>(*temp_box);
        temp_box->inter_level->boxes.push_back(*temp_box_1);
        players[player_index].move(dx, dy);
        next_x -= 2 * dx;
        next_y -= 2 * dy;
        std::vector<Box *> temp_boxes;
        while (is_box(next_x, next_y, boxes)) {
            Box *temp_box_2 = get_box(next_x, next_y);
            if (temp_box_2 == nullptr) {
                return;
            }
            temp_boxes.push_back(temp_box_2);
            next_x -= dx;
            next_y -= dy;
        }
        for (auto temp_box_3: temp_boxes) {
            temp_box_3->move(dx, dy);
        }
    }

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
            if (dy == 1 && dx == 0) {
                return true;
            } else return false;
            break;
        case 2:
            if (dy == -1 && dx == 0) {
                return true;
            } else return false;
            break;
        case 3:
            if (dy == 0 && dx == 1) {
                return true;
            } else return false;
            break;
        case 4:
            if (dy == 0 && dx == -1) {
                return true;
            } else return false;
            break;
        default:
            return false;
    }
}

bool Level::is_box(int x, int y, std::vector<Box> &boxes) {
    for (auto &box: boxes) {
        if (box.x == x && box.y == y) {
            return true;
        }
    }
    return false;
}
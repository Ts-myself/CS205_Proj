#include "../include/level.hpp"

#include <fstream>
#include <string>
#include <iostream>
#include <QMessageBox>

Level::Level() {};

Level::Level(int level_number, Map &map, std::vector<Player *> &players, std::vector<Box *> &boxes) {
    this->level_number = level_number;
    this->map = map;
    this->players = players;
    this->boxes = boxes;
}

void Level::print_level_CIL() {
    char level_print_row[MAP_WIDTH + 1];
    char symbol[] = {'P', 'O', '#', '=', '@', '-', ' ', 'p', 'o'};
    // 'P'-Player, 'O'-Box, '#'-Wall, '='-player check point, '='-box check point, ' '-empty , 'p'-Player on target, 'o'-Box on target
    for (int i = 1; i <= map.height; i++) {
        // draw the map
        for (int j = 1; j <= map.width; j++) {
            level_print_row[j - 1] = symbol[map.map_units[i][j].type];
        }
        // draw the players and boxes
        for (const auto &player: players) {
            if (player->y != i) {
                continue;
            }
            if (map.map_units[player->y][player->x].type == 4) {
                level_print_row[player->x - 1] = symbol[7];
            } else {
                level_print_row[player->x - 1] = symbol[0];
            }
        }
        int a;
        for (const auto &box: boxes) {
            if (box->y != i) {
                continue;
            }
            if (map.map_units[box->y][box->x].type == 3) {
                level_print_row[box->x - 1] = symbol[8];
            } else {
                level_print_row[box->x - 1] = symbol[1];
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

std::vector<int> line_to_int(std::string line) {
    std::vector<int> result;
    std::string temp;
    for (auto i: line) {
        if (i == ' ') {
            result.push_back(std::stoi(temp));
            temp = "";
        } else {
            temp += i;
        }
    }
    result.push_back(std::stoi(temp));
    return result;
}

struct Point2 {
    int x;
    int y;
};

bool Level::load_level(const std::string &level_path, std::vector<Level *> &internal_levels_,
                       std::vector<Box *> &boxes_, Player &player_) {
    std::ifstream level_file(level_path);
    if (!level_file.is_open()) {
        std::cout << "Error: the level file cannot be opened." << std::endl;
        return false;
    }
    std::string line;
    std::vector<std::string> level_info;
    while (getline(level_file, line)) {
        level_info.push_back(line);
    }
    level_file.close();

    if(level_info[0] != "Levels:"){
        std::cout << "Error: the editted level file has a wrong format." << std::endl;
        QMessageBox::warning(nullptr, "Waring",
                             "The editted level file has a wrong format!");
        return false;
    }

    int origin_map_width, origin_map_height;
    std::string origin_map_info;

    int internal_level_number;
    std::vector<int> level_belong_box;

    int boxes_num;
    std::vector<int> boxes_in_level;
    std::vector<int> boxes_enter;
    std::vector<Point2> boxes_enter_pos;
    std::vector<bool> boxes_res;
    std::vector<int> boxes_fa;
    std::vector<Point2> boxes_copy_pos;

    int players_num;

    int offsetLine = 0;
    // origin level
    offsetLine += 1; // offset "Levels:"
    std::vector<int> origin_level_info = line_to_int(level_info[offsetLine]);
    origin_map_width = origin_level_info[0];
    origin_map_height = origin_level_info[1];
    offsetLine += 1;
    for (int i = 0; i < origin_map_height; i++) {
        origin_map_info += level_info[offsetLine + i];
        origin_map_info += '\n';
    }
    Map origin_map(origin_map_width, origin_map_height);
    origin_map.draw_map(origin_map_info);
    map = origin_map;
    level_number = 1;
    offsetLine += origin_map_height;

    // internal levels
    internal_level_number = std::stoi(level_info[offsetLine]);
    offsetLine += 1;
    for (int i = 0; i < internal_level_number; i++) {
        // level belong to box
        level_belong_box.push_back(std::stoi(level_info[offsetLine]));
        offsetLine += 1;
        // width height
        std::vector<int> internal_level_info = line_to_int(level_info[offsetLine]);
        int internal_map_width = internal_level_info[0];
        int internal_map_height = internal_level_info[1];
        offsetLine += 1;
        // enter direction, position to enter
        std::vector<int> internal_level_enter = line_to_int(level_info[offsetLine]);
        boxes_enter.push_back(internal_level_enter[0]);
        boxes_enter_pos.push_back({internal_level_enter[1], internal_level_enter[2]});
        offsetLine += 1;
        // map
        std::string temp_internal_map_info;
        for (int j = 0; j < internal_map_height; j++) {
            temp_internal_map_info += level_info[offsetLine + j];
            temp_internal_map_info += '\n';
        }
        Map internal_map(internal_map_width, internal_map_height);
        internal_map.draw_map(temp_internal_map_info);
        std::vector<Player *> vec_players;
        std::vector<Box *> vec_boxes;
        internal_levels_.push_back(new Level(i, internal_map, vec_players, vec_boxes));
        internal_levels_.back()->level_number = i + 2;
        offsetLine += internal_map_height;
    }

    // boxes
    offsetLine += 1; // offset "Boxes:"
    boxes_num = std::stoi(level_info[offsetLine]);
    offsetLine += 1;
    for (int i = 0; i < boxes_num; i++) {
        std::vector<int> box_info = line_to_int(level_info[offsetLine]);

        boxes_fa.push_back(box_info[3]);
        boxes_copy_pos.push_back({box_info[1], box_info[2]});
        // if (box_info[3] >= 0) {
        //     Box box_copy = *boxes_[box_info[3]];
        //     box_copy.x=box_info[1];
        //     box_copy.y=box_info[2];
        //     boxes_.push_back(&box_copy);
        // } else{

        // }
        boxes_res.push_back(box_info[3] == -2);
        boxes_.push_back(new Box(box_info[1], box_info[2], " "));
        boxes_in_level.push_back(box_info[0]);
        if (box_info[0] == -1) {
            boxes.emplace_back(boxes_.back());
        } else {
            internal_levels_[box_info[0]]->boxes.push_back(boxes_.back());
        }
        // boxes_.back()->enter_direction = boxes_enter[boxes_.size() - 1];
        // boxes_.back()->position_to_enter[0] = boxes_enter_pos[boxes_.size() - 1].x;
        // boxes_.back()->position_to_enter[1] = boxes_enter_pos[boxes_.size() - 1].y;

        offsetLine += 1;
    }

    // players
    offsetLine += 1; // offset "Players:"
    players_num = std::stoi(level_info[offsetLine]);
    offsetLine += 1;
    for (int i = 0; i < players_num; i++) {
        std::vector<int> player_info = line_to_int(level_info[offsetLine]);
        if (player_info[0] == -1) {
            player_.in_level = this;
            players.push_back(&player_);
        } else {
            internal_levels_[player_info[0]]->players.push_back(&player_);
            player_.in_level = internal_levels_[player_info[0]];
        }
        player_.x = player_info[1];
        player_.y = player_info[2];
        offsetLine += 1;
    }

    // internal level belong to box
    for (int i = 0; i < level_belong_box.size(); i++) {
        int belong_box = level_belong_box[i];
        internal_levels_[i]->father_box = boxes_[belong_box];
        boxes_[belong_box]->inter_level = internal_levels_[i];
        boxes_[belong_box]->is_has_internal_level = true;
        boxes_[belong_box]->enter_direction = boxes_enter[i];
        boxes_[belong_box]->position_to_enter[0] = boxes_enter_pos[i].x;
        boxes_[belong_box]->position_to_enter[1] = boxes_enter_pos[i].y;
        if (boxes_res[belong_box]) {
//            boxes_[belong_box]->father_level = boxes_[belong_box]->inter_level;
           boxes_[belong_box]->inter_level->boxes.push_back(boxes_[belong_box]);
            boxes_[belong_box]->inter_level->father_level = boxes_[belong_box]->inter_level;
            boxes_[belong_box]->inter_level->father_box = boxes_[belong_box];
        }else{
            if (boxes_in_level[belong_box] == -1) {
                internal_levels_[i]->father_level = this;
            } else {
                internal_levels_[i]->father_level = internal_levels_[boxes_in_level[belong_box]];
            }
        }
    }

    // box copy and father
    for(int i=0;i<boxes_fa.size();i++){
        if(boxes_fa[i]>=0){
            boxes_[i]->enter_direction = boxes_[boxes_fa[i]]->enter_direction;
            boxes_[i]->position_to_enter[0] = boxes_[boxes_fa[i]]->position_to_enter[0];
            boxes_[i]->position_to_enter[1] = boxes_[boxes_fa[i]]->position_to_enter[1];
            boxes_[i]->is_has_internal_level=true;
            boxes_[i]->inter_level = boxes_[boxes_fa[i]]->inter_level;
        }
    }
    return true;

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
     * 4 6 2 //enter direction, position to enter
     * ######
     * #-=---
     * #-----
     * ######
     * 1
     * 3 4
     * 2 2 3
     * ####
     * #--#
     * #--#
     * 3
     * 4 4
     * 1 2 1
     * #--#
     * #--#
     * #--#
     * ####
     * Boxes:
     * 4 //number of boxes
     * -1 3 2 -1// in nth level, x, y, father_box
     * -1 6 2 -1
     * -1 3 5 -1
     * 0 4 2 -1
     * Players:
     * 1 // number of player
     * -1 5 2 // in nth level, x, y
     */

};

// 0: not movable, 1: movable, 2: movable and push box,
// 3 : out of internal level, 4+: enter internal level,value - 4 is which box is be entered
//int Level::player_movable(size_t player_index, int dx, int dy) {
//    int next_x = players[player_index].x + dx;
//    int next_y = players[player_index].y + dy;
//    //out of map in box
//    if (next_x < 1 || next_x > map.width || next_y < 1 || next_y > map.height){
//        return 3;
//    }
//    int next_type = map.map_units[next_y][next_x].type;
//    if (is_box(next_x,next_y,boxes)){
//        next_type = 1;
//    }
//    if (next_type == 0 || next_type == 2) {
//        return 0;
//    }
//    if (next_type == 6 || next_type == 5) {
//        return 1;
//    }
//    if (next_type == 1){
//        int num_box = 0;
//        while (is_box(next_x,next_y,boxes)) {
//            next_x += dx;
//            next_y += dy;
//            num_box++;
//            if (next_x < 1 || next_x > map.width || next_y < 1) {
//                break;
//            }
//        }
//        //out of map in box
//        if (next_x < 1 || next_x > map.width || next_y < 1 || next_y > map.height){
//            return 3;
//        }
//        int temp_map_type = map.map_units[next_y][next_x].type;
//        //move multiple boxes
//        if (temp_map_type == 6||temp_map_type == 5) {
//            return 2;
//        }
//        if (temp_map_type == 0 || temp_map_type == 2) {
//            next_x -= dx;
//            next_y -= dy;
//            int temp_x = next_x - dx;
//            int temp_y = next_y - dy;
//            for (int i = num_box; i > 0; i--) {
//                Box *temp_box = get_box(next_x, next_y);
//                if (temp_box == nullptr) {
//                    return 0;
//                }
//                if (!temp_box->is_has_internal_level) {
//                    temp_x -= dx;
//                    temp_y -= dy;
//                    next_x -= dx;
//                    next_y -= dy;
//                    continue;
//                }
//                if (!is_can_enter(dx, dy, temp_box->enter_direction)) {
//                    temp_x -= dx;
//                    temp_y -= dy;
//                    next_x -= dx;
//                    next_y -= dy;
//                    continue;
//                }
//                return 4 + i;
//            }
//            return 0;
//        }
//    }
//    return 0;
//
//}
//
//void Level::player_move(size_t player_index, int dx, int dy,int player_movable) {
//    if (player_movable == 0) {
//        std::cout << "player can't move" << std::endl;
//        return;
//    }
//    if (player_movable == 1) {
//        players[player_index].move(dx, dy);
//        return;
//    }
//    if (player_movable == 2) {
//        int next_x = players[player_index].x + dx;
//        int next_y = players[player_index].y + dy;
//        players[player_index].move(dx, dy);
//        std::vector<Box*> temp_boxes;
//        while (is_box(next_x,next_y, boxes)) {
//            Box *temp_box = get_box(next_x, next_y);
//            if (temp_box == nullptr) {
//                return;
//            }
//            temp_boxes.push_back(temp_box);
//            next_x += dx;
//            next_y += dy;
//        }
//        for (auto temp_box : temp_boxes) {
//            temp_box->move(dx, dy);
//        }
//        return;
//    }
//    if (player_movable == 3) {
//        int next_x = players[player_index].x + dx;
//        int next_y = players[player_index].y + dy;
//        if (next_x < 1 || next_x > map.width || next_y < 1 || next_y > map.height){
//            Player temp_player = players[player_index];
//            temp_player.x = father_box->x+dx;
//            temp_player.y = father_box->y+dy;
//            father_level->players.push_back(temp_player);
//            players.erase(players.begin() + 0);
//            return;
//        }
//        players[player_index].move(dx, dy);
//        std::vector<Box*> temp_boxes;
//        while (is_box(next_x,next_y,boxes)) {
//            Box *temp_box_1 = get_box(next_x, next_y);
//            if (temp_box_1 == nullptr) {
//                return;
//            }
//            temp_boxes.push_back(temp_box_1);
//            next_x += dx;
//            next_y += dy;
//            if (next_x < 1 || next_x > map.width || next_y < 1 || next_y > map.height){
//                Box *temp_box = get_box(next_x-dx, next_y-dy);
//                if (temp_box == nullptr) {
//                    return;
//                }
//                boxes.erase(boxes.begin() + (temp_box - &boxes[0]));
//                father_box->inter_level->boxes.push_back(*temp_box);
//                temp_box->x = father_box->x+dx;
//                temp_box->y = father_box->y+dy;
//                temp_box->father_box = father_box->father_box;
//                break;
//            }
//        }
//        for (auto  temp_box : temp_boxes) {
//            temp_box->move(dx, dy);
//        }
//    }
//    if (player_movable >= 4)
//    {
//        int next_x = players[player_index].x;
//        int next_y = players[player_index].y;
//        for (size_t i = 0; i < player_movable-4; i++)
//        {
//            next_x += dx;
//            next_y += dy;
//        }
//        Box *temp_box = get_box(next_x, next_y);
//        if (player_movable-4 == 1)
//        {
//            Player* temp_player = &players[player_index];
//            players.erase(players.begin() + player_index);
//            temp_player->x = temp_box->position_to_enter[0];
//            temp_player->y = temp_box->position_to_enter[1];
//            temp_box->inter_level->players.push_back(*temp_player);
//            return;
//        }
//        Box *temp_box_1 = get_box(next_x-dx, next_y-dy);
//        if (temp_box_1 == nullptr) {
//            return;
//        }
//        temp_box_1->x = temp_box->position_to_enter[0];
//        temp_box_1->y = temp_box->position_to_enter[1];
//        temp_box_1->father_box = temp_box->inter_level->father_box;
//        temp_box->inter_level->boxes.push_back(*temp_box_1);
//        boxes.erase(boxes.begin() + (temp_box_1 - &boxes[0]));
//        players[player_index].move(dx, dy);
//        next_x -= 2*dx;
//        next_y -= 2*dy;
//        std::vector<Box*> temp_boxes;
//        while (is_box(next_x,next_y,boxes)) {
//            Box *temp_box_2 = get_box(next_x, next_y);
//            if (temp_box_2 == nullptr) {
//                return;
//            }
//            temp_boxes.push_back(temp_box_2);
//            next_x -= dx;
//            next_y -= dy;
//        }
//        for (auto temp_box_3 : temp_boxes) {
//            temp_box_3->move(dx, dy);
//        }
//    }
//
//}

void Level::rew_state_Box() {
    for (auto &box: boxes) {
        if (map.map_units[box->y][box->x].type == 4) {
            box->state = 1;
        } else {
            box->state = 0;
        }
    }
}

void Level::rew_state_Player() {
    for (auto &player: players) {
        if (player->state >= 2) {
            continue;
        }
        if (map.map_units[player->y][player->x].type == 3) {
            player->state = 1;
        } else {
            player->state = 0;
        }
    }
}

void Level::rew_state_All() {
    rew_state_Box();
    rew_state_Player();
}

Box *Level::get_box(int x, int y) {
    for (int i = boxes.size() - 1; i >= 0; --i) {
        if (boxes[i]->x == x && boxes[i]->y == y) {
            return boxes[i];
        }
    }
    return nullptr;
}

bool Level::is_win() {
    for (int i = 1; i <= map.height; i++) {
        for (int j = 1; j <= map.width; j++) {
            if (map.map_units[i][j].type == 3 && !is_box(j, i)) {
                return false;
            }
            if (map.map_units[i][j].type == 4 && !is_player(j, i)) {
                return false;
            }
        }
    }
    return true;
}

bool Level::is_box(int x, int y) {
    for (auto &box: boxes) {
        if (box->x == x && box->y == y) {
            return true;
        }
    }
    return false;
}

bool Level::is_player(int x, int y) {
    for (auto &player: players) {
        if (player->x == x && player->y == y) {
            return true;
        }
    }
    return false;
}


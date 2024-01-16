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

bool Level::player_movable(size_t player_index, int dx, int dy) {
    if (map.map_units[players[player_index].y + dy][players[player_index].x + dx].type == 2) {
        return false;
    }
    for (const auto &box: boxes) {
        if (box.x == players[player_index].x + dx && box.y == players[player_index].y + dy) {
            if (map.map_units[box.y + dy][box.x + dx].type == 2) {
                return false;
            }
            // todo: fix by moving multiple boxes
            for (const auto &box2: boxes) {
                if (box2.x == box.x + dx && box2.y == box.y + dy) {
                    return false;
                }
            }
        }
    }
    return true;
}
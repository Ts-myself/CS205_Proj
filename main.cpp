//#include "mainwindow.h"
//
//#include <QApplication>
//
//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    return a.exec();
//}

#include "level.hpp"

#include <iostream>

//todo: replace the operation input with GUI
bool operation_player_move(Level &level1);
Map default_map(8, 8);
Map test_internalBox_map(8, 8);
int main() {


    std::string default_map_str = "########\n"
                                  "#------#\n"
                                  "##-----#\n"
                                  " ####--#\n"
                                  "##--#--#\n"
                                  "#------#\n"
                                  "#----###\n"
                                  "######  \n";
    default_map.draw_map(default_map_str);

    std::vector<Player> default_players{Player(4, 2, " ")};
    std::vector<Box> default_boxes;
    default_boxes.push_back(Box(3, 2, " "));
    default_boxes.push_back(Box(6, 2, " "));
    std::string test_internalBox_map_str = "########\n"
                                           "#------#\n"
                                           "##-----#\n"
                                           "#-------\n"
                                           "##--#--#\n"
                                           "#------#\n"
                                           "#----###\n"
                                           "########\n";

    test_internalBox_map.draw_map(test_internalBox_map_str);
    std::vector<Player> test_internalBox_players;
    std::vector<Box> test_internalBox_boxes;
    default_boxes[0].inter_level = std::make_shared<Level>(2, test_internalBox_map,
                                                           test_internalBox_players, test_internalBox_boxes);
    default_boxes[0].is_has_internal_level = true;
    default_boxes[0].enter_direction = 4;
    default_boxes[0].position_to_enter[0] = 8;
    default_boxes[0].position_to_enter[1] = 4;
    default_boxes[0].inter_level->father_box = std::make_unique<Box>(default_boxes[0]);

    std::cout
            << "Enter 'q' to quit, 'r' to restart, 'w' to move up, 'a' to move left, 's' to move down, 'd' to move right."
            << std::endl;
    Level level1 = Level(1, default_map, default_players, default_boxes);
    std::shared_ptr<Level> temp_level(&level1);
    default_boxes[0].father_level = temp_level;
    std::vector<Level*> levels;
    levels.push_back(&level1);
    levels.push_back(default_boxes[0].inter_level.get());
    std::cout << "Level 1:" << std::endl;
    while (true) {
        Level *current_level = &level1;
        for (auto level : levels) {
            if (!level->players.empty()){
                current_level = level;
            }
        }
        current_level->print_level_CIL();
        if (!operation_player_move(*current_level))
            break;
    }
    return 0;
}

bool operation_player_move(Level &level1) {
    char operator_input;
    std::cin >> operator_input;
    if (operator_input == 'q') {
        return false;
    }
    if (operator_input == 'r') {
        return true;
    }
    if (operator_input == 'w') {
        int movable = level1.player_movable(0, 0, -1);
        level1.player_move(0, 0, -1, movable);
    }
    if (operator_input == 'a') {
        int movable = level1.player_movable(0, -1, 0);
        level1.player_move(0, -1, 0, movable);
    }
    if (operator_input == 's') {
        int movable = level1.player_movable(0, 0, 1);
        level1.player_move(0, 0, 1, movable);
    }
    if (operator_input == 'd') {
        int movable = level1.player_movable(0, 1, 0);
        level1.player_move(0, 1, 0, movable);
    }
    std::cout << "player position: " << level1.players[0].x << "," << level1.players[0].y << std::endl;

    return true;
}
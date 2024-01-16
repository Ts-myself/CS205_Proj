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

int main() {

    Map default_map(8, 8);
    std::string default_map_str = "########\n"
                                  "#------#\n"
                                  "##-----#\n"
                                  " ####--#\n"
                                  "##--#--#\n"
                                  "#------#\n"
                                  "#----###\n"
                                  "######  \n";
    default_map.draw_map(default_map_str);

    std::vector<Player> default_players{Player(2, 2, " ")};
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
    Map test_internalBox_map(8, 8);
    test_internalBox_map.draw_map(test_internalBox_map_str);
    default_boxes[0].internal_level.map = test_internalBox_map;
    default_boxes[0].is_has_internal_level = true;
    default_boxes[0].enter_direction = 4;
    std::cout
            << "Enter 'q' to quit, 'r' to restart, 'w' to move up, 'a' to move left, 's' to move down, 'd' to move right."
            << std::endl;
    Level level1 = Level(1, default_map, default_players, default_boxes);
    std::cout << "Level 1:" << std::endl;
    while (true) {
        level1.print_level_CIL();

        if (!operation_player_move(level1))
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
        if (!level1.player_movable(0, 0, -1))
            return true;
        level1.players[0].move(0, -1);
    }
    if (operator_input == 'a') {
        if (!level1.player_movable(0, -1, 0))
            return true;
        level1.players[0].move(-1, 0);
    }
    if (operator_input == 's') {
        if (!level1.player_movable(0, 0, 1))
            return true;
        level1.players[0].move(0, 1);
    }
    if (operator_input == 'd') {
        if (!level1.player_movable(0, 1, 0))
            return true;
        level1.players[0].move(1, 0);
    }
    std::cout << "player position: " << level1.players[0].x << "," << level1.players[0].y << std::endl;

    return true;
}
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
#include "move.hpp"
#include <iostream>

//todo: replace the operation input with GUI
bool operation_player_move(Player &player);
Map default_map(8, 8);
Map test_internalBox_map(8, 8);
int main() {
    std::vector<Level*> levels;
    std::string default_map_str = "########\n"
                                  "#------#\n"
                                  "##-----#\n"
                                  " ####--#\n"
                                  "##--#--#\n"
                                  "#------#\n"
                                  "#----###\n"
                                  "######  \n";
    default_map.draw_map(default_map_str);
    Player player1(7, 2, " ");
    Player* player1_ptr = &player1;
    std::vector<Player*> default_players{player1_ptr};
    std::vector<Box> default_boxes;
    default_boxes.push_back(Box(3, 2, " "));
    default_boxes.push_back(Box(4, 2, " "));
    default_boxes.push_back(Box(5, 2, " "));
    Level level1(1, default_map, default_players, default_boxes);
    std::string test_internalBox_map_str = "########\n"
                                           "#------#\n"
                                           "##-----#\n"
                                           "#-------\n"
                                           "##--#--#\n"
                                           "#------#\n"
                                           "#----###\n"
                                           "########\n";
    test_internalBox_map.draw_map(test_internalBox_map_str);
    std::vector<Box> test_internalBox_boxes;
    std::vector<Player*> test_internalBox_players;
    Level level2(2, test_internalBox_map, test_internalBox_players, test_internalBox_boxes);
    player1.in_level = &level1;
    std::cout
            << "Enter 'q' to quit, 'r' to restart, 'w' to move up, 'a' to move left, 's' to move down, 'd' to move right."
            << std::endl;
    std::cout << "Level 1:" << std::endl;
    while (true) {
        player1.in_level->print_level_CIL();
        if (!operation_player_move(player1))
            break;
    }
    return 0;
}

bool operation_player_move(Player &player) {
    char operator_input;
    std::cin >> operator_input;
    if (operator_input == 'q') {
        return false;
    }
    if (operator_input == 'r') {
        return true;
    }
    if (operator_input == 'w') {
        move::recurse_move(0,-1,player.x,player.y, nullptr,&player,player.in_level,0);
    }
    if (operator_input == 'a') {
        move::recurse_move(-1,0,player.x,player.y, nullptr,&player,player.in_level,0);
    }
    if (operator_input == 's') {
        move::recurse_move(0,1,player.x,player.y, nullptr,&player,player.in_level,0);
    }
    if (operator_input == 'd') {
        move::recurse_move(1,0,player.x,player.y, nullptr,&player,player.in_level,0);
    }
    std::cout << "player position: " << player.x << "," << player.y << std::endl;

    return true;
}
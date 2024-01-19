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
Map test_internalBox_map2(8, 8);
Map empty_map(5, 5);
int main() {
    std::string default_empty="     \n"
                              "     \n"
                              "     \n"
                              "     \n"
                              "     \n";
    empty_map.draw_map(default_empty);
    std::vector<Player*> empty_players;
    std::vector<Box*> empty_boxes;
    Level empty_level(0,empty_map,empty_players,empty_boxes);

    std::vector<Level*> levels;
    std::string default_map_str = "########\n"
                                  "     -- \n"
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
    std::vector<Box*> default_boxes;

    std::string test_internalBox_map_str = "########\n"
                                           "#-   --#\n"
                                           "##-----#\n"
                                           "#---@-#-\n"
                                           "##--#--#\n"
                                           "#------#\n"
                                           "#----###\n"
                                           "########\n";
    test_internalBox_map.draw_map(test_internalBox_map_str);
    std::vector<Box*> test_internalBox_boxes;
    std::vector<Player*> test_internalBox_players;
    Level level2(2, test_internalBox_map, test_internalBox_players, test_internalBox_boxes);

    std::string test_internalBox_map_str2 ="########\n"
                                           "#-   --#\n"
                                           "##-----#\n"
                                           " ---@-- \n"
                                           "##--#--#\n"
                                           "#------#\n"
                                           "#----###\n"
                                           "########\n";
    int test_position_x[] = {8, 4};
    int test_position_y[] = {1, 4};

    test_internalBox_map2.draw_map(test_internalBox_map_str2);
    std::vector<Box*> test_internalBox_boxes2;
    std::vector<Player*> test_internalBox_players2;
    Level level3(3, test_internalBox_map2, test_internalBox_players2, test_internalBox_boxes2);
    Box* box1 =new Box(5, 2, " ",4,test_position_x,true,&level2,nullptr);
    Box* box2 =new Box(6, 2, " ",4,test_position_y,true,&level3,box1);
    Box* box3 =new Box(8, 2, " ");
    Box box4(*box1);
    box4.x=6;
    box4.y=3;
    Box box5(*box1);
    box5.x=6;
    box5.y=4;


    default_boxes.push_back(box1);
    default_boxes.push_back(box2);
    default_boxes.push_back(box3);
    default_boxes.push_back(&box4);
    default_boxes.push_back(&box5);

    Level level1(1, default_map, default_players, default_boxes);
    level1.father_box = default_boxes[0];
    level1.father_level = &level1;
    level2.father_level = &level1;
    level2.father_box = default_boxes[0];
    level3.father_level = &level2;
    level3.father_box = default_boxes[1];
    player1.in_level = &level1;
    levels.push_back(&level1);
    levels.push_back(&level2);
    levels.push_back(&level3);
    std::cout
            << "Enter 'q' to quit, 'r' to restart, 'w' to move up, 'a' to move left, 's' to move down, 'd' to move right."
            << std::endl;
    std::cout << "Level 1:" << std::endl;
    box1->father_level = &level1;
    while (true) {
        player1.in_level->print_level_CIL();
//        for (auto &box: player1.in_level->boxes) {
//            if (box->is_has_internal_level){
//                //std::cout<<"box "<<"in level "<<box->father_level->level_number<<" position: ("<<box->x<<","<<box->y<<")"<<std::endl;
//                box->inter_level->print_level_CIL();
//            }
//        }
        int count = 0;
        for (auto level: levels) {
            if (!level->is_win()) {
                break;
            } else count++;
        }
        if (count == levels.size()) {
            std::cout << "You win!" << std::endl;
            break;
        }
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
    if (player.in_level==nullptr) {
        std::cout << "You lose!" << std::endl;
        return false;
    }
    std::cout << "player position: " << player.x << "," << player.y << std::endl;

    return true;
}
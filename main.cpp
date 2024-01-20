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
    //player
    Player player1(7, 3, " ");
    //level 0 empty level
    std::string default_empty="     \n"
                              "     \n"
                              "     \n"
                              "     \n"
                              "     \n";
    empty_map.draw_map(default_empty);
    std::vector<Player*> empty_players;
    std::vector<Box*> empty_boxes;
    Level empty_level(0,empty_map,empty_players,empty_boxes);
    //level 1
    std::string default_map_str = "########\n"
                                  "  #  -- \n"
                                  "##----- \n"
                                  " ####--#\n"
                                  "##--#--#\n"
                                  "#------#\n"
                                  "#----###\n"
                                  "######  \n";
    default_map.draw_map(default_map_str);
    std::vector<Player*> default_players;
    std::vector<Box*> default_boxes;
    Level level1(1, default_map, default_players, default_boxes);
    //level 2
    std::string test_internalBox_map_str = "########\n"
                                           "#-   --#\n"
                                           "##-----#\n"
                                           "#---@- -\n"
                                           "##--#--#\n"
                                           "#------#\n"
                                           "#----###\n"
                                           "########\n";
    test_internalBox_map.draw_map(test_internalBox_map_str);
    std::vector<Box*> test_internalBox_boxes;
    std::vector<Player*> test_internalBox_players;
    Level level2(2, test_internalBox_map, test_internalBox_players, test_internalBox_boxes);
    //level 3
    std::string test_internalBox_map_str2 ="########\n"
                                           "#-   --#\n"
                                           "##-----#\n"
                                           " ---@-- \n"
                                           "##--#--#\n"
                                           "#------#\n"
                                           "#----###\n"
                                           "########\n";
    test_internalBox_map2.draw_map(test_internalBox_map_str2);
    std::vector<Box*> test_internalBox_boxes2;
    std::vector<Player*> test_internalBox_players2;
    Level level3(3, test_internalBox_map2, test_internalBox_players2, test_internalBox_boxes2);
    //store all levels
    std::vector<Level*> levels;
    //store all levels
    levels.push_back(&level1);
    levels.push_back(&level2);
    levels.push_back(&level3);

    //boxes
    int test_position_x[] = {8, 4};
    int test_position_y[] = {1, 4};
    Box* box1 =new Box(5, 3, " ",4,test_position_x,true,&level2, nullptr);
    Box* box2 =new Box(8, 3, " ",3,test_position_y,true,&level3, nullptr);
    Box* box3 =new Box(6, 3, " ");

    //box push in levels
    level1.boxes.push_back(box1);
    level1.boxes.push_back(box2);
    level1.boxes.push_back(box3);

    //box1 as recurse box
    box1->inter_level->father_level=&level2;
    box1->inter_level->father_box=box1;

    //greedy snake
    level1.father_box=box1;
    level1.father_level=&level1;

    //multiple reference of box2
    Box box4=*box2;
    box4.x=7;
    box4.y=5;
    Box box5=*box2;
    box5.x=7;
    box5.y=6;
    level1.boxes.push_back(&box4);
    level1.boxes.push_back(&box5);
    box2->inter_level->father_box=box1;
    box2->inter_level->father_level=&level1;

    //player in level 1
    level1.players.push_back(&player1);
    player1.in_level = &level1;
    std::cout
            << "Enter 'q' to quit, 'r' to restart, 'w' to move up, 'a' to move left, 's' to move down, 'd' to move right."
            << std::endl;
    std::cout << "Level 1:" << std::endl;
    while (true) {
        player1.in_level->print_level_CIL();
        bool is_print[levels.size()];
        for (int i = 0; i < levels.size(); i++) {
            is_print[i] = false;
        }
        //print all box's internal level
        for (auto & boxe : player1.in_level->boxes) {
            if (boxe->is_has_internal_level){
                if (!is_print[boxe->inter_level->level_number-1]){
                    boxe->inter_level->print_level_CIL();
                    is_print[boxe->inter_level->level_number-1]=true;
                }
            }
        }
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
        int a = player1.x;
        int b = player1.y;
        int c = player1.in_level->level_number;
        if (!operation_player_move(player1))
            break;
        //check if player enter the recurse box
        if (a != player1.x || b != player1.y) {
            if (a-player1.x>1||a-player1.x<-1||b-player1.y>1||b-player1.y<-1){
                if (c==player1.in_level->level_number){
                    std::cout << "You enter the recurse box!" << std::endl;
                    std::cout << "Level " << player1.in_level->level_number << ":" << std::endl;
                }
            }
        }
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
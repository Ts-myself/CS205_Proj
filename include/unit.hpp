#pragma once

#include <string>
#include <memory>

class Unit
{
public:
    Unit();
    Unit(int x, int y, int type, std::string img_path);

    int x, y;
    int type; // 0 = player, 1 = box, 2 = wall, 3 = box_checkPoint, 4 = player_checkPoint, 5 = floor, 6 = empty
    std::string img_path;
    virtual void move(int dx, int dy);
    int state;// 0: normal, 1: on checkpoint , 2+: in box ,state - 1: the layer of the box
};
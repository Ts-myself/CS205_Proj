#include "../include/unit.hpp"

Unit::Unit() : x(0), y(0), img_path(" "){};

Unit::Unit(int x, int y, int type, std::string img_path) : x(x), y(y), type(type), img_path(img_path){};

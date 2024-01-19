#include "../include/map.hpp"

#include <iostream>
#include <string>
#include <vector>

Map::Map() = default;

Map::Map(int width, int height) {
    this->width = width;
    this->height = height;
    for (int i = 1; i <= height; i++) {
        for (int j = 1; j <= width; j++) {
            map_units[i][j] = Unit(i, j, 5, " ");
        }
    }
}

std::vector<std::string> split(std::string str, std::string pattern) {
    std::string::size_type pos;
    std::vector<std::string> result;
    size_t size = str.size();
    for (int i = 0; i < size; i++) {
        pos = str.find(pattern, i);
        if (pos < size) {
            std::string s = str.substr(i, pos - i);
            result.push_back(s);
            i = (int) (pos + pattern.size() - 1);
        }
    }
    return result;
}

bool Map::draw_map(std::string img_info) {
    std::vector<std::string> img_info_split = split(img_info, "\n");
    if (img_info_split.size() != height) {
        std::cout << "Error: the height of the map is not correct." << std::endl;
        return false;
    }
    for (int i = 0; i < height; i++) {
        if (img_info_split[i].size() != width) {
            std::cout << "Error: the width of the map is not correct." << std::endl;
            return false;
        }
        for (int j = 0; j < width; j++) {
            switch (img_info_split[i][j]) {
                case '#':
                    map_units[i + 1][j + 1] = Unit(i + 1, j + 1, 2, " ");
                    break;
                case '=':
                    map_units[i + 1][j + 1] = Unit(i + 1, j + 1, 3, " ");
                    break;
                case '@':
                    map_units[i + 1][j + 1] = Unit(i + 1, j + 1, 4, " ");
                    break;
                case '-':
                    map_units[i + 1][j + 1] = Unit(i + 1, j + 1, 5, " ");
                    break;
                case ' ':
                    map_units[i + 1][j + 1] = Unit(i + 1, j + 1, 6, " ");
                    break;
                default:
                    std::cout << "Error: the map contains invalid characters." << std::endl;
                    return false;
            }
        }
    }
    return true;
}

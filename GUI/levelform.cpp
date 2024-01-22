#include "levelform.h"
#include "ui_levelform.h"
#include "../include/move.hpp"

#include <QLabel>
#include <QMessageBox>
#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include <fstream>

levelForm::levelForm(QWidget * parent)
:

QWidget (parent)
, ui(new Ui::levelForm) {
    ui->setupUi(this);
}

levelForm::~levelForm() {
    delete ui;
    for (auto &level: internal_levels) {
        delete level;
    }
    for (auto &box: boxes) {
        delete box;
    }
}

void levelForm::on_quitBotton_clicked() {
    this->close();
}

int find_box_level(Box *box, std::vector<Level *> &internal_levels) {
    for (int i = 0; i < internal_levels.size(); i++) {
        for (auto &box_in_level: internal_levels[i]->boxes) {
            if (box == box_in_level) {
                return i;
            }
        }
    }
    return -1;
}

void levelForm::saveStep() {
    Record record;
    //pos
    for (auto &box: boxes) {
        record.box_pos.push_back({box->x, box->y});
    }
    record.player_pos = {player.x, player.y};
    //in_which_level
    for (auto &box: boxes) {
        record.box_in_level.push_back(find_box_level(box, internal_levels));
    }
    bool in_internal = false;
    for (int i = 0; i < internal_levels.size(); i++) {
        if (player.in_level == internal_levels[i]) {
            in_internal = true;
            record.player_in_level = i;
            break;
        }
    }
    if (!in_internal) {
        record.player_in_level = -1;
    }
    undoRecords.push_back(record);
}

void levelForm::keyPressEvent(QKeyEvent *ev) {
    if (ev->key() == Qt::Key_W) {
        saveStep();
        move::recurse_move(0, -1, player.x, player.y, nullptr, &player, player.in_level, 0);
    } else if (ev->key() == Qt::Key_A) {
        saveStep();
        move::recurse_move(-1, 0, player.x, player.y, nullptr, &player, player.in_level, 0);
    } else if (ev->key() == Qt::Key_S) {
        saveStep();
        move::recurse_move(0, 1, player.x, player.y, nullptr, &player, player.in_level, 0);
    } else if (ev->key() == Qt::Key_D) {
        saveStep();
        move::recurse_move(1, 0, player.x, player.y, nullptr, &player, player.in_level, 0);
    }
    if (player.in_level == nullptr) {
        std::cout << "You lose!" << std::endl;
        QMessageBox::information(this, tr("Lose"),
                                 tr("You lose!"),
                                 QMessageBox::Yes);
        this->close();
        return;
    }
    player.in_level->print_level_CIL();
    print_level_GUI(*player.in_level, player);
    int count = 0;
    for (auto level: internal_levels) {
        if (!level->is_win()) {
            break;
        } else count++;
    }
    if (ownLevel.is_win())
        count++;
    if (count == internal_levels.size() + 1) {
        std::cout << "You win!" << std::endl;
        QMessageBox::information(this, tr("Win"),
                                 tr("You win!"),
                                 QMessageBox::Yes);
        this->close();
    }
}

//mode: 1-level1, 2-level1, 3-level3, 4-load editted level
bool levelForm::initLevel(int mode, std::string add) {
    levelMode = mode;
    // ui->levelInfoLabel->setText(QString::fromStdString("level " + std::to_string(levelMode)));
    Level initLevel;
    ownLevel = initLevel;
    internal_levels.clear();
    boxes.clear();
    std::string path = std::filesystem::current_path().string();
    if (mode == 1) {
        std::string level1Info = "Level 1\n\n"
                                 "Show basic Sokuban Rules\n"
                                 "Pushing more then 1 boxes\n"
                                 "Player's check point\n\n"
                                 "Internal structure of box(visible in CLI instead of GUI).\n"
                                 "Go to the empty 5x5, which we denote it as LOSE";
        ui->levelInfoLabel->setText(QString::fromStdString(level1Info));
        std::string level1_path = path + "\\data\\level1" + add;
        if (!ownLevel.load_level(level1_path, internal_levels, boxes, player, level_infos))
            return false;
    } else if (mode == 2) {
        std::string level2Info = "Level 2\n\n"
                                 "Show Recursive Box\n"
                                 "GO out of A, then out of B\n\n"
                                 "Recursive overflow\n"
                                 "Greedy Snake\n"
                                 "Multiple reference\n"
                                 "(Use reset to implment the above stuations)";
        ui->levelInfoLabel->setText(QString::fromStdString(level2Info));
        std::string level2_path = path + "\\data\\level2" + add;
        if (!ownLevel.load_level(level2_path, internal_levels, boxes, player, level_infos))
            return false;
    } else if (mode == 3) {
        std::string level3Info = "Level 3\n\n"
                                 "Show Recursive Box\n"
                                 "Go from A to B, where A is next to B\n";
        ui->levelInfoLabel->setText(QString::fromStdString(level3Info));
        std::string level3_path = path + "\\data\\level3" + add;
        if (!ownLevel.load_level(level3_path, internal_levels, boxes, player, level_infos))
            return false;
    } else if (mode == 4) {
        std::string edit_level_path = path + "\\data\\editLevel" + add;
        if (!ownLevel.load_level(edit_level_path, internal_levels, boxes, player, level_infos))
            return false;
    }

    player.in_level->print_level_CIL();
    bool is_print[internal_levels.size() + 1];
    for (int i = 0; i < internal_levels.size() + 1; i++) {
        is_print[i] = false;
    }
    for (auto &box_print: player.in_level->boxes) {
        if (box_print->is_has_internal_level) {
            if (!is_print[box_print->inter_level->level_number - 1]) {
                box_print->inter_level->print_level_CIL();
                is_print[box_print->inter_level->level_number - 1] = true;
            }
        }
    }
    print_level_GUI(*player.in_level, player);
    return true;
}

bool levelForm::loadLevel(int mode) {
    levelMode = mode;
    // ui->levelInfoLabel->setText(QString::fromStdString("level " + std::to_string(levelMode)));
    Level initLevel;
    ownLevel = initLevel;
    internal_levels.clear();
    boxes.clear();
    Player initPlayer;
    player = initPlayer;
    std::string path = std::filesystem::current_path().string();
    if (mode == 1) {
        std::string level1Info = "Level 1\n\n"
                                 "Show basic Sokuban Rules\n"
                                 "Pushing more then 1 boxes\n"
                                 "Player's check point\n\n"
                                 "Internal structure of box(visible in CLI instead of GUI).\n"
                                 "Go to the empty 5x5, which we denote it as LOSE";
        ui->levelInfoLabel->setText(QString::fromStdString(level1Info));
        std::string level1_path = path + "\\data\\level1_save.txt";
        if (!ownLevel.load_level(level1_path, internal_levels, boxes, player, level_infos))
            return false;
    } else if (mode == 2) {
        std::string level2Info = "Level 2\n\n"
                                 "Show Recursive Box\n"
                                 "GO out of A, then out of B\n\n"
                                 "Recursive overflow\n"
                                 "Greedy Snake\n"
                                 "Multiple reference\n"
                                 "(Use reset to implment the above stuations)";
        ui->levelInfoLabel->setText(QString::fromStdString(level2Info));
        std::string level2_path = path + "\\data\\level2_save.txt";
        if (!ownLevel.load_level(level2_path, internal_levels, boxes, player, level_infos))
            return false;
    } else if (mode == 3) {
        std::string level3Info = "Level 3\n\n"
                                 "Show Recursive Box\n"
                                 "Go from A to B, where A is next to B\n";
        ui->levelInfoLabel->setText(QString::fromStdString(level3Info));
        std::string level3_path = path + "\\data\\level3_save.txt";
        if (!ownLevel.load_level(level3_path, internal_levels, boxes, player, level_infos))
            return false;
    } else if (mode == 4) {
        std::string edit_level_path = path + "\\data\\editLevel_save.txt";
        if (!ownLevel.load_level(edit_level_path, internal_levels, boxes, player, level_infos))
            return false;
    }

    player.in_level->print_level_CIL();
    bool is_print[internal_levels.size() + 1];
    for (int i = 0; i < internal_levels.size() + 1; i++) {
        is_print[i] = false;
    }
    for (auto &box_print: player.in_level->boxes) {
        if (box_print->is_has_internal_level) {
            if (!is_print[box_print->inter_level->level_number - 1]) {
                box_print->inter_level->print_level_CIL();
                is_print[box_print->inter_level->level_number - 1] = true;
            }
        }
    }
    print_level_GUI(*player.in_level, player);
    return true;
}

void levelForm::print_level_GUI(const Level &curLevel, const Player &player1) {
    int level_height = curLevel.map.height;
    int level_width = curLevel.map.width;

    // QLabel curLabels[MAP_HEIGHT][MAP_WIDTH];
    QPixmapCache::clear();
    for (int i = level_height; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            QWidget * widgetItem = ui->levelLayout->itemAtPosition(i, j)->widget();
            QLabel * labelItem = qobject_cast<QLabel *>(widgetItem);
            labelItem->clear();
            labelItem->setText("");
        }
    }
    for (int i = level_width; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            QWidget * widgetItem = ui->levelLayout->itemAtPosition(j, i)->widget();
            QLabel * labelItem = qobject_cast<QLabel *>(widgetItem);
            labelItem->clear();
            labelItem->setText("");
        }
    }
    for (int i = 0; i < level_height; i++) {
        for (int j = 0; j < level_width; j++) {
            QPixmap pic;
            std::string imgs_path = std::filesystem::current_path().string() + "\\data";

            bool isPlayer = false, isBox = false;
            for (const auto &player: curLevel.players) {
                if (player->x == j + 1 && player->y == i + 1) {
                    isPlayer = true;
                    if (curLevel.map.map_units[player->y][player->x].type == 4) {
                        std::string img_path = imgs_path + "\\playerAtCheckPoint.png";
                        pic.load(QString::fromStdString(img_path));
                    } else {
                        std::string img_path = imgs_path + "\\player.png";
                        pic.load(QString::fromStdString(img_path));
                    }
                }
            }

            for (const auto &box: curLevel.boxes) {
                if (box->x == j + 1 && box->y == i + 1) {
                    isBox = true;
                    if (curLevel.map.map_units[box->y][box->x].type == 3) {
                        std::string img_path = imgs_path + "\\boxAtCheckPoint.png";
                        pic.load(QString::fromStdString(img_path));
                    } else {
                        std::string img_path = imgs_path + "\\box.png";
                        pic.load(QString::fromStdString(img_path));
                    }
                }
            }

            if (!isPlayer && !isBox) {
                // 0 = player, 1 = box, 2 = wall, 3 = box_checkPoint, 4 = player_checkPoint, 5 = floor, 6 = empty
                switch (curLevel.map.map_units[i + 1][j + 1].type) {
                    case 2: {
                        std::string img_path = imgs_path + "\\wall.png";
                        pic.load(QString::fromStdString(img_path));
                        break;
                    }
                    case 3: {
                        std::string img_path = imgs_path + "\\box_checkPoint.png";
                        pic.load(QString::fromStdString(img_path));
                        break;
                    }
                    case 4: {
                        std::string img_path = imgs_path + "\\player_checkPoint.png";
                        pic.load(QString::fromStdString(img_path));
                        break;
                    }
                    case 5: {
                        std::string img_path = imgs_path + "\\floor.png";
                        pic.load(QString::fromStdString(img_path));
                        break;
                    }
                    case 6: {
                        std::string img_path = imgs_path + "\\empty.png";
                        pic.load(QString::fromStdString(img_path));
                        break;
                    }
                    default:;
                }
            }
            // curLabels[i][j].setPixmap(pic);
            QWidget * widgetItem = ui->levelLayout->itemAtPosition(i, j)->widget();
            QLabel * labelItem = qobject_cast<QLabel *>(widgetItem);
            labelItem->setPixmap(pic);
        }
    }
};

void levelForm::on_resetBotton_clicked() {
    initLevel(levelMode, ".txt");
}

std::vector<int> line_2_int(std::string line) {
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

void levelForm::on_undoBotton_clicked() {
    if (undoRecords.size() == 0) {
        return;
    }
    Record last_step = undoRecords.back();
    undoRecords.pop_back();

    std::vector<std::string> undo_info = level_infos;
    for (int i = 0; i < undo_info.size(); i++) {
        if (undo_info[i].find("Boxes:") != std::string::npos) {
            for (int j = i + 2; j < i + 2 + boxes.size(); j++) {
                // change the undo_info[j] to the last step
                std::vector<int> box_info = line_2_int(undo_info[j]);
                undo_info[j] =
                        std::to_string(last_step.box_in_level[j - i - 2]) + " " + std::to_string(last_step.box_pos[j - i - 2].x) +
                        " " + std::to_string(last_step.box_pos[j - i - 2].y) + " " + std::to_string(box_info[3]);
            }
            undo_info[i + 4 + boxes.size()] =
                    std::to_string(last_step.player_in_level) + " " + std::to_string(last_step.player_pos.x) + " " +
                    std::to_string(last_step.player_pos.y);
            break;
        }
    }
    Level initLevel;
    ownLevel = initLevel;
    for(auto level_: internal_levels){
        delete level_;
    }
    for(auto box_: boxes){
        delete box_;
    }
    std::vector<Level*> init_internal_levels;
    std::vector<Box*> init_boxes;
    internal_levels = init_internal_levels;
    boxes = init_boxes;
    ownLevel.load_level_by_info(undo_info, internal_levels, boxes, player);
    std::cout<<"-----UNDO-----\n";
    player.in_level->print_level_CIL();
    bool is_print[internal_levels.size() + 1];
    for (int i = 0; i < internal_levels.size() + 1; i++) {
        is_print[i] = false;
    }
    for (auto &box_print: player.in_level->boxes) {
        if (box_print->is_has_internal_level) {
            if (!is_print[box_print->inter_level->level_number - 1]) {
                box_print->inter_level->print_level_CIL();
                is_print[box_print->inter_level->level_number - 1] = true;
            }
        }
    }
    print_level_GUI(*player.in_level, player);
}


void levelForm::on_loadButton_clicked()
{
    initLevel(levelMode, "_save.txt");
    std::cout<<"-----LOAD-----\n";
}


void levelForm::on_saveButton_clicked()
{
    Record record;
    //pos
    for (auto &box: boxes) {
        record.box_pos.push_back({box->x, box->y});
    }
    record.player_pos = {player.x, player.y};
    //in_which_level
    for (auto &box: boxes) {
        record.box_in_level.push_back(find_box_level(box, internal_levels));
    }
    bool in_internal = false;
    for (int i = 0; i < internal_levels.size(); i++) {
        if (player.in_level == internal_levels[i]) {
            in_internal = true;
            record.player_in_level = i;
            break;
        }
    }
    if (!in_internal) {
        record.player_in_level = -1;
    }

    std::vector<std::string> level_info_save = level_infos;

    for (int i = 0; i < level_info_save.size(); i++) {
        if (level_info_save[i].find("Boxes:") != std::string::npos) {
            for (int j = i + 2; j < i + 2 + boxes.size(); j++) {
                // change the undo_info[j] to the last step
                std::vector<int> box_info = line_2_int(level_info_save[j]);
                level_info_save[j] =
                    std::to_string(record.box_in_level[j - i - 2]) + " " + std::to_string(record.box_pos[j - i - 2].x) +
                    " " + std::to_string(record.box_pos[j - i - 2].y) + " " + std::to_string(box_info[3]);
            }
            level_info_save[i + 4 + boxes.size()] =
                std::to_string(record.player_in_level) + " " + std::to_string(record.player_pos.x) + " " +
                std::to_string(record.player_pos.y);
            break;
        }
    }

    // save the std::vector<std::string> level_info_save into a .txt file line by line
    std::string path = std::filesystem::current_path().string();
    std::string save_path;
    if (levelMode == 1) {
        save_path = path + "\\data\\level1_save.txt";
    } else if (levelMode == 2) {
        save_path = path + "\\data\\level2_save.txt";
    } else if (levelMode == 3) {
        save_path = path + "\\data\\level3_save.txt";
    } else if (levelMode == 4) {
        save_path = path + "\\data\\editLevel_save.txt";
    }
    std::ofstream save_file(save_path);
    for (auto &line: level_info_save) {
        save_file << line << std::endl;
    }
    save_file.close();

    std::cout<<"-----SAVE-----\n";
}


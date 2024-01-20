#include "levelform.h"
#include "ui_levelform.h"
#include "../include/move.hpp"

#include <QLabel>
#include <QMessageBox>
#include <iostream>
#include <filesystem>

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

void levelForm::keyPressEvent(QKeyEvent *ev) {
    if (ev->key() == Qt::Key_W) {
        move::recurse_move(0, -1, player.x, player.y, nullptr, &player, player.in_level, 0);
    } else if (ev->key() == Qt::Key_A) {
        move::recurse_move(-1, 0, player.x, player.y, nullptr, &player, player.in_level, 0);
    } else if (ev->key() == Qt::Key_S) {
        move::recurse_move(0, 1, player.x, player.y, nullptr, &player, player.in_level, 0);
    } else if (ev->key() == Qt::Key_D) {
        move::recurse_move(1, 0, player.x, player.y, nullptr, &player, player.in_level, 0);
    }
    if (player.in_level==nullptr) {
        std::cout << "You lose!" << std::endl;
        QMessageBox::information(this, tr("Lose"),
                             tr("You lose!"),
                             QMessageBox::Yes);
        this->close();
    }
    player.in_level->print_level_CIL();
    print_level_GUI(*player.in_level);
    int count = 0;
    for (auto level: internal_levels) {
        if (!level->is_win()) {
            break;
        } else count++;
    }
    if(ownLevel.is_win())
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
void levelForm::initLevel(int mode) {
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
        std::string level1_path = path + "\\data\\level1.txt";
        ownLevel.load_level(level1_path, internal_levels, boxes, player);
    } else if (mode == 2) {
        std::string level2Info = "Level 2\n\n"
                                 "Show Recursive Box\n"
                                 "GO out of A, then out of B\n";
        ui->levelInfoLabel->setText(QString::fromStdString(level2Info));
        std::string level2_path = path + "\\data\\level2.txt";
        ownLevel.load_level(level2_path, internal_levels, boxes, player);
    } else if (mode == 3) {
        std::string level3Info = "Level 3\n\n"
                                 "Show Recursive Box\n"
                                 "Go from A to B, where A is next to B\n";
        ui->levelInfoLabel->setText(QString::fromStdString(level3Info));
        std::string level3_path = path + "\\data\\level3.txt";
        ownLevel.load_level(level3_path, internal_levels, boxes, player);
    } else if (mode == 4) {
        std::string edit_level_path = path + "\\data\\editLevel.txt";
        ownLevel.load_level(edit_level_path, internal_levels, boxes, player);
    }

    player.in_level->print_level_CIL();
    print_level_GUI(*player.in_level);
}

void levelForm::print_level_GUI(const Level &curLevel) {
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
                    if (curLevel.map.map_units[player->x][player->y].type == 4) {
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
                    if (curLevel.map.map_units[box->x][box->y].type == 3) {
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
    initLevel(levelMode);
}


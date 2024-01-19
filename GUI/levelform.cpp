#include "levelform.h"
#include "ui_levelform.h"
#include "../include/move.hpp"

#include <QLabel>

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
    player.in_level->print_level_CIL();
    print_level_GUI(*player.in_level);
}

//mode: 1-level1, 2-level1, 3-level3, 4-load editted level
void levelForm::initLevel(int mode) {
    levelMode = mode;
    // ui->levelInfoLabel->setText(QString::fromStdString("level " + std::to_string(levelMode)));
    Level initLevel;
    ownLevel = initLevel;
    internal_levels.clear();
    boxes.clear();
    if (mode == 1) {
        std::string level1_path = "D:\\Data\\university\\Study\\Sophomore_Fisrt\\C++\\Proj\\CS205_Proj\\data\\level1.txt";
        ownLevel.load_level(level1_path, internal_levels, boxes, player);
    } else if (mode == 2) {
        std::string level2_path = " ";
        ownLevel.load_level(level2_path, internal_levels, boxes, player);
    } else if (mode == 3) {
        std::string level3_path = " ";
        ownLevel.load_level(level3_path, internal_levels, boxes, player);
    } else if (mode == 4) {
        std::string edit_level_path = " ";
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
            labelItem->setText("");
        }
    }
    for (int i = level_width; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            QWidget * widgetItem = ui->levelLayout->itemAtPosition(j, i)->widget();
            QLabel * labelItem = qobject_cast<QLabel *>(widgetItem);
            labelItem->setText("");
        }
    }
    for (int i = 0; i < level_height; i++) {
        for (int j = 0; j < level_width; j++) {
            QPixmap pic;
            std::string imgs_path = "D:\\Data\\university\\Study\\Sophomore_Fisrt\\C++\\Proj\\CS205_Proj\\data";

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


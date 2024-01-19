#include "levelform.h"
#include "ui_levelform.h"

#include <QLabel>

levelForm::levelForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::levelForm)
{
    ui->setupUi(this);
}

levelForm::~levelForm()
{
    delete ui;
}

void levelForm::on_quitBotton_clicked()
{
    this->close();
}

void levelForm::keyPressEvent(QKeyEvent *ev){
    if(ev->key() == Qt::Key_W){
        int movable = ownLevel.player_movable(0, 0, -1);
        ownLevel.player_move(0, 0, -1, movable);
    } else if(ev->key() == Qt::Key_A){
        int movable = ownLevel.player_movable(0, -1, 0);
        ownLevel.player_move(0, -1, 0, movable);
    } else if(ev->key() == Qt::Key_S){
        int movable = ownLevel.player_movable(0, 0, 1);
        ownLevel.player_move(0, 0, 1, movable);
    } else if(ev->key() == Qt::Key_D){
        int movable = ownLevel.player_movable(0, 1, 0);
        ownLevel.player_move(0, 1, 0, movable);
    }
    ownLevel.print_level_CIL();
    print_level_GUI(ownLevel);
}

//mode: 1-level1, 2-level1, 3-level3, 4-load editted level
void levelForm::initLevel(int mode){
    // todo: change by using loading files
    Map default_map(8, 8);
    Map test_internalBox_map(8, 8);
    std::string default_map_str = "########\n"
                                  "#------#\n"
                                  "##-----#\n"
                                  " ####--#\n"
                                  "##--#--#\n"
                                  "#------#\n"
                                  "#----###\n"
                                  "######  \n";
    default_map.draw_map(default_map_str);

    std::vector<Player> default_players{Player(4, 2, " ")};
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

    test_internalBox_map.draw_map(test_internalBox_map_str);
    std::vector<Player> test_internalBox_players;
    std::vector<Box> test_internalBox_boxes;
    default_boxes[0].inter_level = std::make_shared<Level>(2, test_internalBox_map,
                                                           test_internalBox_players, test_internalBox_boxes);
    default_boxes[0].is_has_internal_level = true;
    default_boxes[0].enter_direction = 4;
    default_boxes[0].position_to_enter[0] = 8;
    default_boxes[0].position_to_enter[1] = 4;
    default_boxes[0].inter_level->father_box = std::make_unique<Box>(default_boxes[0]);
    ownLevel = Level(1, default_map, default_players, default_boxes);

    ownLevel.print_level_CIL();
    print_level_GUI(ownLevel);
}

void levelForm::print_level_GUI(const Level &curLevel){
    int level_height = curLevel.map.height;
    int level_width = curLevel.map.width;

    // QLabel curLabels[MAP_HEIGHT][MAP_WIDTH];
    QPixmapCache::clear();
    for(int i=level_height;i<10;i++){
        for(int j=0;j<10;j++){
            QWidget *widgetItem =ui->levelLayout->itemAtPosition(i, j)->widget();
            QLabel *labelItem = qobject_cast<QLabel*>(widgetItem);
            labelItem->setText("");
        }
    }
    for(int i=level_width;i<10;i++){
        for(int j=0;j<10;j++){
            QWidget *widgetItem =ui->levelLayout->itemAtPosition(j, i)->widget();
            QLabel *labelItem = qobject_cast<QLabel*>(widgetItem);
            labelItem->setText("");
        }
    }
    for (int i = 0; i < level_height; i++) {
        for (int j = 0; j < level_width; j++) {
            QPixmap pic;
            std::string imgs_path = "D:\\Data\\university\\Study\\Sophomore_Fisrt\\C++\\Proj\\CS205_Proj\\data";

            bool isPlayer=false, isBox =false;
            for (const auto &player: curLevel.players) {
                if(player.x == j+1 && player.y == i+1){
                    isPlayer = true;
                    if (curLevel.map.map_units[player.x][player.y].type == 3) {
                        std::string img_path = imgs_path + "\\playerAtCheckPoint.png";
                        pic.load(QString::fromStdString(img_path));
                    } else {
                        std::string img_path = imgs_path + "\\player.png";
                        pic.load(QString::fromStdString(img_path));
                    }
                }
            }

            for (const auto &box: curLevel.boxes) {
                if(box.x == j+1 && box.y == i+1){
                    isBox = true;
                    if (curLevel.map.map_units[box.x][box.y].type == 4) {
                        std::string img_path = imgs_path + "\\boxAtCheckPoint.png";
                        pic.load(QString::fromStdString(img_path));
                    } else {
                        std::string img_path = imgs_path + "\\box.png";
                        pic.load(QString::fromStdString(img_path));
                    }
                }
            }

            if(!isPlayer && !isBox){
                 // 0 = player, 1 = box, 2 = wall, 3 = box_checkPoint, 4 = player_checkPoint, 5 = floor, 6 = empty
                switch(curLevel.map.map_units[i+1][j+1].type)
                {
                case 2:{
                    std::string img_path = imgs_path + "\\wall.png";
                    pic.load(QString::fromStdString(img_path));
                    break;
                }
                case 3:{
                    std::string img_path = imgs_path + "\\box_checkPoint.png";
                    pic.load(QString::fromStdString(img_path));
                    break;
                }
                case 4:{
                    std::string img_path = imgs_path + "\\player_checkPoint.png";
                    pic.load(QString::fromStdString(img_path));
                    break;
                }
                case 5:{
                    std::string img_path = imgs_path + "\\floor.png";
                    pic.load(QString::fromStdString(img_path));
                    break;
                }
                case 6:{
                    std::string img_path = imgs_path + "\\empty.png";
                    pic.load(QString::fromStdString(img_path));
                    break;
                }
                default:;
                }
            }
            // curLabels[i][j].setPixmap(pic);
            QWidget *widgetItem =ui->levelLayout->itemAtPosition(i, j)->widget();
            QLabel *labelItem = qobject_cast<QLabel*>(widgetItem);
            labelItem->setPixmap(pic);
        }
    }
};

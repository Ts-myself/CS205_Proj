#include <iostream>

#include "mainwindow.h"
//#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
//        , ui(new Ui::MainWindow)
{
//    ui->setupUi(this);
}

MainWindow::~MainWindow() {
//    delete ui;
}

void MainWindow::startGame() {
    Map default_map(5, 5);
    std::vector<Player> default_players{Player(2, 2, " ")};
    std::vector<Box> default_boxes;
    Level level1 = Level(1, default_map, default_players, default_boxes);
    std::cout << "Level 1:" << std::endl;
    level1.print_level_CIL();
}
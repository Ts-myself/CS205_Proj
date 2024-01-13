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
    Level level1 = Level(1, default_map, std::vector<Player>(), std::vector<Box>());
    std::cout << "Level 1:" << std::endl;
    level1.print_level_CIL();
}
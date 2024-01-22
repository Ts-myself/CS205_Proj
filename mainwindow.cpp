#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_level1Botton_clicked()
{
    std::cout<<"LEVEL 1\n";
    level1.show();
    level1.initLevel(1, ".txt");
    // this->hide();
}

void MainWindow::on_level2Botton_clicked()
{
    std::cout<<"LEVEL 2\n";
    level2.show();
    level2.initLevel(2, ".txt");
    // this->hide();
}
void MainWindow::on_level3Botton_clicked()
{
    std::cout<<"LEVEL 3\n";
    level3.show();
    level3.initLevel(3, ".txt");
    // this->hide();
}


void MainWindow::on_quitBotton_clicked()
{
    std::cout<<"QUIT\n";
    this->close();
}


void MainWindow::on_editLevelBotton_clicked()
{
    std::cout<<"EDIT LEVEL\n";
    editForm.show();
    editForm.init();
}



void MainWindow::on_edittedLevelButton_clicked()
{
    std::cout<<"EDITTED LEVEL\n";
    if(edittedLevel.initLevel(4, ".txt"))
        edittedLevel.show();
}


#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "include/level.hpp"


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
    level1.show();
    level1.initLevel(1);
    // this->hide();
}

void MainWindow::on_level2Botton_clicked()
{
    level2.show();
    level2.initLevel(2);
    // this->hide();
}
void MainWindow::on_level3Botton_clicked()
{
    level3.show();
    level3.initLevel(3);
    // this->hide();
}

void MainWindow::on_quitBotton_clicked()
{
    this->close();
}


void MainWindow::on_editLevelBotton_clicked()
{
    editForm.show();
    editForm.init();
}


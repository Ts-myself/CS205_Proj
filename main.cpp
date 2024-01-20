#include "mainwindow.h"
#include "GUI/logindialog.h"

#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    LogInDialog lgd;
    auto lgd_exec = lgd.exec();
    std::cout<<"----------------Sokuban with Recursion----------------\n";
    a.setQuitOnLastWindowClosed(true);
    while(lgd_exec == QDialog::Accepted){
        std::cout<<"-----------level1---level2---level3-----------\n";
        std::cout<<"-------------edit level---quit----------------\n";
        w.show();
        return a.exec();
    }

    return a.exec();
}

#include "mainwindow.h"
#include "GUI/logindialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    LogInDialog lgd;
    auto lgd_exec = lgd.exec();
    while(lgd_exec == QDialog::Accepted){
        w.show();
        return a.exec();
    }

    return a.exec();
}

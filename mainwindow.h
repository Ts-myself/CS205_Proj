#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "level.hpp"

#include <QMainWindow>

//QT_BEGIN_NAMESPACE
//namespace Ui
//{
//    class MainWindow;
//}
//QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

    static void startGame();

private:
//    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

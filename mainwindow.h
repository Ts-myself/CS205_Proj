#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "GUI/levelform.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    levelForm level1;
    levelForm level2;
    levelForm level3;

private slots:
    void on_level1Botton_clicked();
    void on_level2Botton_clicked();
    void on_level3Botton_clicked();

    void on_quitBotton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

#ifndef LEVELFORM_H
#define LEVELFORM_H

#include "../include/level.hpp"

#include <QWidget>
#include <QKeyEvent>
#include <QPixmapCache>

namespace Ui {
class levelForm;
}

class levelForm : public QWidget
{
    Q_OBJECT

public:
    explicit levelForm(QWidget *parent = nullptr);
    ~levelForm();

    void initLevel(int mode);
    void print_level_GUI(const Level &level);
    Level ownLevel;

protected:
    void keyPressEvent(QKeyEvent *ev);
    // void keyReleaseEvent(QKeyEvent *ev);

private slots:
    void on_quitBotton_clicked();

private:
    Ui::levelForm *ui;
};

#endif // LEVELFORM_H

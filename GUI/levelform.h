#ifndef LEVELFORM_H
#define LEVELFORM_H

#include "../include/level.hpp"
#include "../include/player.hpp"

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

    bool initLevel(int mode);
    void print_level_GUI(const Level &level, const Player &player);
    Level ownLevel;
    std::vector<Level*> internal_levels;
    std::vector<Box*> boxes;
    Player player;
    int levelMode;

protected:
    void keyPressEvent(QKeyEvent *ev);
    // void keyReleaseEvent(QKeyEvent *ev);

private slots:
    void on_quitBotton_clicked();

    void on_resetBotton_clicked();

private:
    Ui::levelForm *ui;
};

#endif // LEVELFORM_H

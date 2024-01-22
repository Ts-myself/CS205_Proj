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

struct Record{
    std::vector<Point2> box_pos;
    std::vector<int> box_in_level;
    Point2 player_pos;
    int player_in_level;
};

class levelForm : public QWidget
{
    Q_OBJECT

public:
    explicit levelForm(QWidget *parent = nullptr);
    ~levelForm();

    bool initLevel(int mode, std::string add);
    bool loadLevel(int mode);
    void print_level_GUI(const Level &level, const Player &player);
    void saveStep();

    Level ownLevel;
    std::vector<Level*> internal_levels;
    std::vector<Box*> boxes;
    Player player;

    int levelMode;
    std::vector<std::string> level_infos;
    std::vector<Record> undoRecords;

protected:
    void keyPressEvent(QKeyEvent *ev);
    // void keyReleaseEvent(QKeyEvent *ev);

private slots:
    void on_quitBotton_clicked();

    void on_resetBotton_clicked();

    void on_undoBotton_clicked();


    void on_loadButton_clicked();

    void on_saveButton_clicked();

private:
    Ui::levelForm *ui;
};

#endif // LEVELFORM_H

#ifndef EDITLEVELFORM_H
#define EDITLEVELFORM_H

#include <QWidget>

namespace Ui {
class editLevelForm;
}

class editLevelForm : public QWidget
{
    Q_OBJECT

public:
    explicit editLevelForm(QWidget *parent = nullptr);
    ~editLevelForm();

    void init();

private slots:
    void on_quitBotton_4_clicked();

    void on_resetBotton_4_clicked();

private:
    Ui::editLevelForm *ui;
};

#endif // EDITLEVELFORM_H

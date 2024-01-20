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

private:
    Ui::editLevelForm *ui;
};

#endif // EDITLEVELFORM_H

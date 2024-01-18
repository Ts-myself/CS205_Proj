#ifndef LEVELFORM_H
#define LEVELFORM_H

#include <QWidget>

namespace Ui {
class levelForm;
}

class levelForm : public QWidget
{
    Q_OBJECT

public:
    explicit levelForm(QWidget *parent = nullptr);
    ~levelForm();


private slots:
    void on_quitBotton_clicked();

private:
    Ui::levelForm *ui;
};

#endif // LEVELFORM_H

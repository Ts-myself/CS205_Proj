#include "levelform.h"
#include "ui_levelform.h"

levelForm::levelForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::levelForm)
{
    ui->setupUi(this);
}

levelForm::~levelForm()
{
    delete ui;
}

void levelForm::on_quitBotton_clicked()
{
    this->close();
}


#include "editlevelform.h"
#include "ui_editlevelform.h"

editLevelForm::editLevelForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::editLevelForm)
{
    ui->setupUi(this);
}

editLevelForm::~editLevelForm()
{
    delete ui;
}

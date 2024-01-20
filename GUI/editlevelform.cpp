#include "editlevelform.h"
#include "ui_editlevelform.h"

#include <filesystem>
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

void editLevelForm::init(){
    // QLayoutItem * layoutItem = ui->sideLayout_4->itemAt(3);
    // QWidget * widget = layoutItem->widget();
    // QLabel * edit1 = widget->findChild<QLabel *>("editExampleLabel");
    // QLabel * edit2 = widget->findChild<QLabel *>("editFormLabel");
    // edit1->setPixmap(pic1);
    // edit2->setPixmap(pic2);

    std::string path = std::filesystem::current_path().string() + "\\data";
    QPixmap pic1;
    QPixmap pic2;
    pic1.load(QString::fromStdString(path+"\\editEaxmple.png"));
    pic2.load(QString::fromStdString(path+"\\editForm.png"));
    ui->editFormLabel->setPixmap(pic2);
    ui->editExampleLabel->setPixmap(pic1);

}

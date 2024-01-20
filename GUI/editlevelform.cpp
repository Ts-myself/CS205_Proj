#include "editlevelform.h"
#include "ui_editlevelform.h"

#include <filesystem>
#include <QApplication>
#include <QMainWindow>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QFile>
#include <QTextStream>

editLevelForm::editLevelForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::editLevelForm)
{
    ui->setupUi(this);
    ui->levelEdit->setFixedSize(200,600);
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

void editLevelForm::on_quitBotton_4_clicked()
{
    this->close();
}


void editLevelForm::on_resetBotton_4_clicked()
{
    std::string file_path = std::filesystem::current_path().string() + "\\data\\editLevel.txt";
    QFile file(QString::fromStdString(file_path));
    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
    {
        file.close();
        qDebug() << "File cleared successfully.";
    }
    else
    {
        qDebug() << "Failed to clear file.";
    }

    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream << ui->levelEdit->toPlainText();
        file.close();
        qDebug() << "File saved successfully.";
    }
    else
    {
        qDebug() << "Failed to save file.";
    }
    this->close();
}


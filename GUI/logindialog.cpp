#include "logindialog.h"
#include "ui_logindialog.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <QMessagebox>

LogInDialog::LogInDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LogInDialog)
{
    ui->setupUi(this);
}

LogInDialog::~LogInDialog()
{
    delete ui;
}

void readUserAndPwd(std::vector<std::string> &user,std::vector<std::string> &pwd){
    std::ifstream file("data/user_pwd.txt");

    if (!file) {
        return;
    }

    std::string line;
    int lineCount = 1;

    while (std::getline(file, line)) {
        if (lineCount % 2 == 1) {
            user.push_back(line);
        } else {
            pwd.push_back(line);
        }
        lineCount++;
    }

    file.close();
}

void LogInDialog::on_loginButton_clicked()
{
    std::vector<std::string> user;
    std::vector<std::string> password;
    readUserAndPwd(user,password);
    if(std::find(user.begin(),user.end(),ui->usernameEdit->text().toStdString())!=user.end() &&
        std::find(password.begin(),password.end(),ui->passwordEdit->text().toStdString())!=password.end() )
    {
        accept();
    } else {
        QMessageBox::warning(this, tr("Waring"),
                             tr("user name or password error!"),
                             QMessageBox::Yes);
    }
}


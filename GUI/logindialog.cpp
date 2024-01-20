#include "logindialog.h"
#include "ui_logindialog.h"

// #include <filesystem>
#include <fstream>
#include <vector>
#include <string>
#include <QMessagebox>
#include <filesystem>

LogInDialog::LogInDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LogInDialog)
{
    ui->setupUi(this);
    ui->passwordEdit->setEchoMode(QLineEdit::EchoMode::Password);
    QPixmap pic;
    std::string img_path = std::filesystem::current_path().string() + "\\data";
    pic.load(QString::fromStdString(img_path+"\\head.png"));
    ui->headLabel->setPixmap(pic);
}

LogInDialog::~LogInDialog()
{
    delete ui;
}

void readUserAndPwd(std::vector<std::string> &user,std::vector<std::string> &pwd){
    // std::filesystem::path path = std::filesystem::current_path();
    // std::string path_str = path.string();
    // std::string file_path = path_str + "\\data\\user_pwd.txt";
    std::string file_path = std::filesystem::current_path().string() + "\\data\\user_pwd.txt";
    // std::string file_path = ":\\..\\data\\user_pwd.txt";

    std::ifstream file(file_path);

    if (!file.is_open()) {
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
    readUserAndPwd(user, password);
    std::string user_input = ui->usernameEdit->text().toStdString();
    std::string pwd_input = ui->passwordEdit->text().toStdString();
    int user_pos=-1;
    for(int i=0;i<user.size();i++)
        if(user[i]==user_input){
            user_pos = i;
            break;
        }
    if(user_pos != -1)
    {
        if(password[user_pos] == pwd_input)
            accept();
        else
            QMessageBox::warning(this, tr("Waring"),
                                 tr("password is wrong!"),
                                 QMessageBox::Yes);
    } else {
        QMessageBox::warning(this, tr("Waring"),
                             tr("user name does not exist!"),
                             QMessageBox::Yes);
    }
}


#include "logindialog.h"
#include "ui_logindialog.h"

// #include <filesystem>
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
    // std::filesystem::path path = std::filesystem::current_path();
    // std::string path_str = path.string();
    // std::string file_path = path_str + "\\data\\user_pwd.txt";
    // todo: change the path (qmake will change the source)
    std::string file_path = "D:\\Data\\university\\Study\\Sophomore_Fisrt\\C++\\Proj\\CS205_Proj\\data\\user_pwd.txt";

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
    int user_pos=-1, pwd_pos=-1;
    for(int i=0;i<user.size();i++)
        if(user[i]==user_input){
            user_pos = i;
            break;
        }
    for(int i=0;i<password.size();i++)
        if(password[i]==pwd_input){
            pwd_pos = i;
            break;
        }
    if(user_pos != -1 && pwd_pos != -1 && user_pos == pwd_pos)
    {
        accept();
    } else {
        QMessageBox::warning(this, tr("Waring"),
                             tr("user name or password error!"),
                             QMessageBox::Yes);
    }
}


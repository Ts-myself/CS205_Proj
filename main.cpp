#include "mainwindow.h"
#include "GUI/logindialog.h"

#include <QApplication>
#include <QMainWindow>
#include <QTextEdit>
#include <iostream>
#include <iostream>
#include <streambuf>

// Custom stream buffer that redirects output to a QTextEdit widget
class TextEditStreamBuffer : public std::streambuf
{
public:
    explicit TextEditStreamBuffer(QTextEdit* textEdit)
        : m_textEdit(textEdit)
    {
    }

protected:
    virtual int_type overflow(int_type c) override
    {
        if (c != EOF)
        {
            m_textEdit->insertPlainText(QString(QChar(c)));
        }
        return c;
    }

    virtual std::streamsize xsputn(const char* s, std::streamsize n) override
    {
        m_textEdit->insertPlainText(QString::fromLatin1(s, n));
        return n;
    }

private:
    QTextEdit* m_textEdit;
};

// Custom message handler for redirecting qDebug, qInfo, qWarning, and qCritical to QTextEdit
void messageHandler(QtMsgType type, const QMessageLogContext&, const QString& msg)
{
    static QTextEdit* textEdit = nullptr;
    if (!textEdit)
        return;

    switch (type)
    {
    case QtDebugMsg:
        textEdit->insertPlainText("[Debug] " + msg + "\n");
        break;
    case QtInfoMsg:
        textEdit->insertPlainText("[Info] " + msg + "\n");
        break;
    case QtWarningMsg:
        textEdit->insertPlainText("[Warning] " + msg + "\n");
        break;
    case QtCriticalMsg:
        textEdit->insertPlainText("[Critical] " + msg + "\n");
        break;
    default:
        break;
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QMainWindow mainWindow;
    QTextEdit textEdit;
    mainWindow.setCentralWidget(&textEdit);
    mainWindow.setWindowTitle("Mock CLI");
    mainWindow.resize(400, 600);
    mainWindow.move(100, 100);
    mainWindow.show();
    TextEditStreamBuffer coutStreamBuffer(&textEdit);
    TextEditStreamBuffer cerrStreamBuffer(&textEdit);
    std::cout.rdbuf(&coutStreamBuffer);
    std::cerr.rdbuf(&cerrStreamBuffer);
    textEdit.setReadOnly(true);
    qInstallMessageHandler(messageHandler);


    MainWindow w;
    LogInDialog lgd;
    auto lgd_exec = lgd.exec();
    std::cout<<"--------------Sokuban with Recursion--------------\n";
    a.setQuitOnLastWindowClosed(true);
    while(lgd_exec == QDialog::Accepted){
        std::cout<<"-----------level1---level2---level3-----------\n";
        std::cout<<"-------------edit level---quit----------------\n";
        w.show();
        return a.exec();
    }

    return a.exec();
}

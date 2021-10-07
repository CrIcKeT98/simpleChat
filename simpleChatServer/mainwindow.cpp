#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&this->server, SIGNAL(signalRecvMsg()), this, SLOT(slotRecvMsg()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_sendButton_clicked()
{
    //read input message
    auto s = ui->sendMsgTextEdit->text();
    const char* buff = s.toStdString().c_str();

    server.sendMessage(buff, sizeof(buff));
}

void MainWindow::slotRecvMsg(){
    //get current time
    QString result_str = QTime::currentTime().toString();

    //get receive message
    QString buff(this->server.getMessage());

    result_str += ": " + buff + '\n';

    ui->recvMsgTextEdit->insertPlainText(result_str);
}

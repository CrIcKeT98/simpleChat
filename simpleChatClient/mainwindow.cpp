#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&this->client, SIGNAL(signalRecvMsg()), this, SLOT(slotRecvMsg()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_sendButton_clicked()
{
    auto s = ui->sendMsgTextEdit->text();
    //char* buff = s.toStdString().c_str();
    client.sendMessage(s.toStdString().c_str(), s.size());
}

void MainWindow::slotRecvMsg(){
    //get current time
    QString result_str = QTime::currentTime().toString();

    //get receive message
    QString buff(this->client.getMessage());

    result_str += ": " + buff + '\n';

    ui->recvMsgTextEdit->insertPlainText(result_str);
}

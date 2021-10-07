#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>
#include "serversocket.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void showMessage(char* buff, int size);
    ~MainWindow();

private slots:
    void on_sendButton_clicked();
    void slotRecvMsg();

private:
    Ui::MainWindow *ui;
    serverSocket server;

};
#endif // MAINWINDOW_H

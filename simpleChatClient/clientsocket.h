#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <thread>
#include <QObject>
#include <QMessageBox>
#include "connectWrapper.h"

class clientSocket : public QObject
{
    Q_OBJECT
private:
    int sock;
    sockaddr_in addr;
    char recv_buff[1024];
    std::thread th;

    const int PORT = 27015;

public:
    clientSocket();
    size_t sendMessage(const char* buff, int size);
    void workingCycle(int listener);
    char* getMessage();
    ~clientSocket();

signals:
    void signalError(const QString&);
    void signalRecvMsg();
};

#endif // CLIENTSOCKET_H

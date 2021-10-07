#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <thread>
#include <QObject>
#include <QMessageBox>

class serverSocket : public QObject
{
    Q_OBJECT
private:
    int sock, listener;
    sockaddr_in addr;
    char recv_buff[1024];
    int bytes_read;
    std::thread th;

    const int PORT = 27015;
public:
    serverSocket();
    size_t sendMessage(const char* buff, int size);
    char* getMessage();
    void workingCycle(int listener);
    ~serverSocket();

signals:
    void signalRecvMsg();
};

#endif // SERVERSOCKET_H

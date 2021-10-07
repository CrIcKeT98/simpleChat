#include "clientsocket.h"

clientSocket::clientSocket()
{
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0)
    {
        //todo error
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    if(connectWrapper::connectWrap(sock, reinterpret_cast<sockaddr*>(&addr), sizeof(addr))< 0)
    {
        QMessageBox msgBox;
        QMessageBox::warning(&msgBox, "Error!", "Server is not running!");
        exit(0);
    }

    th = std::thread(&clientSocket::workingCycle, std::ref(*this), std::ref(sock));
    th.detach();
}

size_t clientSocket::sendMessage(const char* buff, int size){
    return send(sock, buff, size, 0);
}

void clientSocket::workingCycle(int sock){
    while(1){
        recv(sock, recv_buff, sizeof(recv_buff), 0);
        emit signalRecvMsg();
    }
}

char* clientSocket::getMessage(){
    return recv_buff;
}

clientSocket::~clientSocket(){
    shutdown(sock, SHUT_RDWR);
    close(sock);
}

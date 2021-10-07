#include "serversocket.h"

serverSocket::serverSocket()
{
    //create Internet TCP/IP socket
    listener = socket(AF_INET, SOCK_STREAM, 0);

    if(listener < 0){
        QMessageBox msgBox;
        QMessageBox::warning(&msgBox, "Error!", "Failed to create socket!");
        exit(0);
    }

    //initialize sockaddr_in structure
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    //bind socket and sockaddr
    if(bind(listener, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) < 0){
        QMessageBox msgBox;
        QMessageBox::warning(&msgBox, "Error!", "Port 27015 is busy!");
        exit(0);
    }

    //change socket mode to work mode
    listen(listener, 1);

    th = std::thread(&serverSocket::workingCycle, std::ref(*this), std::ref(listener));
    th.detach();
}

size_t serverSocket::sendMessage(const char* buff, int size){
    return send(sock, buff, size, 0);
}

char* serverSocket::getMessage(){
    return recv_buff;
}

void serverSocket::workingCycle(int listener){
    while(1){
        sock = accept(listener, NULL, NULL);
        if(sock < 0)
        {
            QMessageBox msgBox;
            QMessageBox::warning(&msgBox, "Error!", "Failed to create new session!");
            exit(0);
        }

        while(1)
        {
            bytes_read = recv(sock, recv_buff, 1024, 0);
            if(bytes_read <= 0) break;
            emit signalRecvMsg();
        }
    }
}

serverSocket::~serverSocket(){
    shutdown(sock, SHUT_RDWR);
    close(sock);

    shutdown(listener, SHUT_RDWR);
    close(listener);
}

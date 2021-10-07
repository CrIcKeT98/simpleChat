#ifndef CONNECTWRAPPER_H
#define CONNECTWRAPPER_H
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

//Qt have function connect() in global space, so that is trouble
class connectWrapper{
public:
    connectWrapper() {};
    static int connectWrap(int sockfd, struct sockaddr *serv_addr, int addrlen){
        return connect(sockfd, serv_addr, addrlen);
    }
};

#endif // CONNECTWRAPPER_H

//
// Created by Fenghe Xu on 2019-10-20.
//

#ifndef SOCKET_SERVER_ACCEPTOR_H
#define SOCKET_SERVER_ACCEPTOR_H

struct arg_struct {
    struct sockaddr_in* clientAddr;
    int clntSock;
};

void* acceptor(void* ptrArgs);
#endif //SOCKET_SERVER_ACCEPTOR_H

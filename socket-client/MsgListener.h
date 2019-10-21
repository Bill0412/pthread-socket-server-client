//
// Created by Fenghe Xu on 2019-10-22.
//

#ifndef SOCKET_CLIENT_MSGLISTENER_H
#define SOCKET_CLIENT_MSGLISTENER_H
struct arg_struct {
    int sock;
};

void*  msgListener(void* arg);
#endif //SOCKET_CLIENT_MSGLISTENER_H

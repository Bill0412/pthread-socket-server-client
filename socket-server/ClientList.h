//
// Created by Fenghe Xu on 2019-10-22.
//

#ifndef SOCKET_SERVER_CLIENTLIST_H
#define SOCKET_SERVER_CLIENTLIST_H
struct ClientNode {
    int sock;
    char ip_address[64]; // i.e. clntName
    int port;
    struct ClientNode* next;
};

struct ClientList {
    struct ClientNode* handle;
    int count;
};



struct ClientList* InitClientList();

void AppendClientList(int sock, char* ip_address, int port);

char* FormatClientList();

void RemoveNodeFromList(int sock);



#endif //SOCKET_SERVER_CLIENTLIST_H

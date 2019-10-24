//s
// Created by Fenghe Xu on 2019-10-22.
//

#include "ClientList.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

struct ClientList *client_list;

struct ClientNode* CreateClientNode(int sock, char* ip_address, int port);
char* FormatClientNode(struct ClientNode* node);
int str2int(char* s, int len);


struct ClientList* InitClientList()
{
    client_list = (struct ClientList*) malloc (sizeof(struct ClientList));
    client_list->count = 0;
    client_list->handle = NULL;
    return client_list;
}

void AppendClientListUtility(struct ClientNode* node)
{
    node->next = NULL;

    if(!client_list->handle) {
        client_list->handle = node;
        return;
    }

    client_list->count++;

    struct ClientNode* n = client_list->handle;
    for(; n->next; n = n->next);
    n->next = node;
}

struct ClientNode* CreateClientNode(int sock, char* ip_address, int port)
{
    struct ClientNode* node = (struct ClientNode*) malloc (sizeof(struct ClientNode));

    node->next = NULL;
    node->sock = sock;
    node->port = port;

    memcpy(node->ip_address, ip_address, strlen(ip_address) + 1);

    return node;
}

void AppendClientList(int sock, char* ip_address, int port)
{
    AppendClientListUtility(CreateClientNode(sock, ip_address, port));
}

// from display to formatted string
char* FormatClientNode(struct ClientNode* node)
{
    char s[128];
    sprintf(s, "{%d:%s:%d}", node->sock, node->ip_address, node->port);
    char* ptr = (char*) malloc (sizeof(char) * (strlen(s) + 1));
    memcpy(ptr, s, strlen(s) + 1);
    return ptr;
}

// todo: fix potential bug
char* FormatClientList()
{
    const int res_limit = 1024;
    char res[res_limit] = "";

    for(struct ClientNode* node = client_list->handle; node; node = node->next) {
        char* sub = FormatClientNode(node);
        if(!*res) { // first sub
            sprintf(res, "{list:{%s", sub);
        } else {
            sprintf(res, "%s,%s", res, sub);
        }
        free(sub);
    }
    char* res1[res_limit];
    sprintf(res1, "%s}", res);


    char* r = (char*)malloc(sizeof(char) * (res_limit + 1));
    memcpy(r, res1, strlen(res1) + 1);
    return r;
}

void RemoveNodeFromList(int sock)
{
    // todo: fix node not removed
    struct ClientNode* prevNode = client_list->handle;
    for(struct ClientNode* node = client_list->handle; node; prevNode = node, node = node->next) {
        if(node->sock == sock) {
            // remove the node
            // if it is the handle
            client_list->count--;
            if(client_list->handle == node) {
                client_list->handle = node->next;
                free(node);
                return;
            }

            // if it is the rear node
            if(!node->next) {
                free(node);
                prevNode->next = NULL;
                return;
            }

            // if in the middle
            prevNode->next = node->next;
            free(node);
        }
    }
}

void RetrieveListFromString(char* strList)
{
    // parse the string
    // string format: {{sock:ip:port},{},{}}
    int leftCurly = 0;  // match left curly braces with a right one {}

    char* prevC = strList + 1;
    for(char* c = prevC; ; ) {
        if(*c != '{') {
            // find { of the next element
            c++;
            continue;
        }

        // str to number conversion
        // find the first and last digit of the client
        char* sock = c + 1;
        for(; *sock != ':' ; sock++);
        int sockLen = sock - c - 1;
        int clntSock = str2int(c + 1, sockLen);

        // retrieve the ip by query :
        char* ip = sock + 1;
        char* port = ip;
        for(; *port != ':'; port++);
        char clntIP[64];
        int lenIP = port - ip;
        memcpy(clntIP, ip, lenIP);
        clntIP[lenIP] = '\0';

        // retrieve the port by query }
        port++;
        char* endPort = port;

        for(; *endPort != '}'; endPort++);
        int clntPort = str2int(port, endPort - port);

        // update the node list(dummy method, since the list is considered to be short)
        RemoveNodeFromList(clntSock);
        AppendClientList(clntSock, clntIP, clntPort);

        if(endPort[1] == '}') {
            break;
        }
        // set c for next start
        c = endPort;
    }
}

void PrettyPrintClientList()
{
    printf("sock id \t ip address \t port\n");

    for(struct ClientNode* node = client_list->handle; node; node = node->next) {
        printf("\t%d \t\t %s \t\t %d\n", node->sock, node->ip_address, node->port);
    }
    fflush(stdout);
}

int str2int(char* s, int len)
{
    int res = 0;

    for(int i = 0; i < len; i++) {
        res += ((s[i] - '0') * pow(10, len - 1 - i));
    }

    return res;
}
//s
// Created by Fenghe Xu on 2019-10-22.
//

#include "ClientList.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include "DieWithMessage.h"

#define res_limit 1024

struct ClientList *client_list;

struct ClientNode* CreateClientNode(int sock, char* ip_address, int port);
char* FormatClientNode(struct ClientNode* node);

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
    char res[res_limit];

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

struct ClientList* GetClientList()
{
    return client_list;
}

void* UpdateClientList()
{
    for( ; ; ) {
        int error, ret;
        socklen_t len = sizeof(error);
        for(struct ClientNode* node = GetClientList()->handle; node; node = node->next) {
            sleep(1);
            char alive_msg = "{alive}";
            int numBytesSent = send(node->sock, alive_msg, sizeof(alive_msg), 0);
            if(numBytesSent < 0) {
                 printf("Client %d disconnected unexpectedly.\n", node->sock);
                 RemoveNodeFromList(node->sock);
                 printf("Removed  client sock %s from the client list\n", node->sock);
                 fflush(stdout);
             }
         }
    }
}
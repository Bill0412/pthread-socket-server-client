//
// Created by Fenghe Xu on 2019-10-20.
//

#include "Acceptor.h"
#include <netinet/in.h>
#include <stdio.h>
#include <arpa/inet.h>
#include "Practical.h"
#include <stdlib.h>

void* acceptor(void* ptrArgs)
 {
    struct arg_struct* a;
    a = (struct arg_struct *) ptrArgs;
    struct sockaddr_in clntAddr = *a->clientAddr;

    char clntName[INET_ADDRSTRLEN]; // String to contain client address
    if (inet_ntop(AF_INET, &clntAddr.sin_addr.s_addr, clntName, sizeof(clntName)) != NULL)
        printf("Handling client %s/%d\n", clntName, ntohs(clntAddr.sin_port));
    else
        puts("Unable to get client address");

    HandleTCPClient(a->clntSock);
    free(a->clientAddr);
    free(a);
}
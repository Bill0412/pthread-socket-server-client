//
// Created by Fenghe Xu on 2019-10-22.
//

#include "MsgListener.h"
#include <sys/types.h>
#include <string.h>
#include "DieWithMessage.h"
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include "Globals.h"
int stall;

#define BUFSIZE 1024

void*  msgListener(void* arg)
{
    char* buffer[BUFSIZE];

    struct arg_struct* a = arg;
    int sock = a->sock;
    free(a);

    // receive the server hello message
    ssize_t numBytesRcvd = recv(sock, buffer, BUFSIZE, 0);
    if (numBytesRcvd < 0)
        DieWithSystemMessage("recv() failed.");


    printf("Message received from socket server %d: %s\n", sock, buffer);
    fflush(stdout);
    stall = FALSE;

    for( ; ; ) {
        numBytesRcvd = recv(sock, buffer, BUFSIZE, 0);

        if(numBytesRcvd <= 0)
            continue;

        printf("Message received from socket server %d: %s\n", sock, buffer);
        printf("System Message: Enter to continue");
        fflush(stdout);
    }
}
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
#include <pthread.h>
int stall;
int sock;
#define BUFSIZE 1024

void PressAnyKeyToContinue()
{
    printf("(PRESS ANY KEY TO CONTINUE) ");
    fflush(stdout);
    getchar();
    fflush(stdin);
}

void*  msgListener(void* arg)
{
    char* buffer[BUFSIZE];

    // receive the server hello message
    ssize_t numBytesRcvd = recv(sock, buffer, BUFSIZE, 0);
    if (numBytesRcvd < 0)
        DieWithSystemMessage("recv() failed.");


    printf("Message received from socket server %d: %s\n", sock, buffer);
    fflush(stdout);
    stall = FALSE;

    for( ; ; ) {
        if(sock != -1) {
            numBytesRcvd = recv(sock, buffer, BUFSIZE, 0);

            if(numBytesRcvd <= 0)
                continue;

            // printf("Message received from socket server %d: [%s]\n", sock, buffer);
            // printf("System Message: Enter to continue");

            // issue solved by adding this
            char* inst = buffer; // why this works ????
            int instLen = 6;

            for(char* c = buffer; *(inst + 1) != 'l'; c++) {
                if(*c == '}') {
                    *c = '\0';
                    break;
                }
            }

            // issue is here solved

            // printf("before enter buffer == 't'\n");
            // printf("buffer: [%s]\n", buffer);
            // fflush(stdout);


            if(*(inst + 1) == 't') {

                printf("Server time: %s\n", inst + instLen);
                fflush(stdout);
                PressAnyKeyToContinue();
                stall = FALSE;
            }

            if(*(inst + 1) == 'n') {
                printf("Server name: %s\n", inst + instLen);
                fflush(stdout);
                PressAnyKeyToContinue();
                stall = FALSE;
            }

            if(*(inst + 1) == 'l') {
                printf("Server client list: %s\n", inst + instLen);
                fflush(stdout);
                PressAnyKeyToContinue();
                stall = FALSE;
            }


        } else {
            printf("Exiting the remaining socket thread...\n");
            fflush(stdout);
            stall = FALSE;
            pthread_exit(0);
        }
    }
}
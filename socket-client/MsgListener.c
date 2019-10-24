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

void pressEnterToContinue()
{
    printf("\n(PRESS ENTER TO CONTINUE) ");
    fflush(stdout);
    fflush(stdin);
    getchar();
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

#if 1
    printf("Message received from socket server %d: %s\n", sock, buffer);
    fflush(stdout);
#endif
    stall = FALSE;


    for( ; ; ) {
        if(sock != -1) {
            numBytesRcvd = recv(sock, buffer, BUFSIZE, 0);

            if(numBytesRcvd <= 0)
                continue;
#if DEBUG
            printf("Message received from socket server %d: [%s]\n", sock, buffer);
            fflush(stdout);
            // printf("System Message: Enter to continue");
#endif
            // issue solved by adding this
            char* inst = buffer; // why this works ????

            char* instruction[5];
            memcpy(instruction, inst + 1, 4);
            instruction[5] = '\0';
#if DEBUG
            printf("Instruction: %s\n", instruction);
#endif
            int isTime = !strcmp(instruction, "time");
            int isName = !strcmp(instruction, "name");
            int isList = !strcmp(instruction, "list");
            int isFromClnt = !strcmp(instruction, "clnt");

            int instLen = 6;
            if( isTime || isName || isFromClnt) {
                for(char* c = buffer;; c++) {
                    if(*c == '}') {
                        *c = '\0';
                        break;
                    }
                }
#if DEBUG
                printf("instLen: %d\n", instLen);
#endif
                if(isTime) {

                    printf("Server time: %s\n", inst + instLen);
                    fflush(stdout);
                    pressEnterToContinue();
                    stall = FALSE;
                }

                if(isName) {
                    printf("Server name: %s\n", inst + instLen);
                    fflush(stdout);
                    pressEnterToContinue();
                    stall = FALSE;
                }

                if(isFromClnt) {
                    printf("Client Message Relayed: %s\n", inst + instLen);
                    fflush(stdout);
                    pressEnterToContinue();
                    stall = FALSE;
                }


            } else if (isList){
                printf("Server client list: %s\n", inst + instLen);
                fflush(stdout);

                pressEnterToContinue();
                stall = FALSE;
            } else {
                // other input
                printf("Other server message: %s\n", inst);
                fflush(stdout);
                // pressAnyKeyToContinue();
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
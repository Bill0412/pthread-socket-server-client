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

            printf("Message received from socket server %d: [%s]\n", sock, buffer);
            fflush(stdout);
            // printf("System Message: Enter to continue");

            // issue solved by adding this
            char* inst = buffer; // why this works ????
            int instLen = 6;
            char* instruction[5];
            memcpy(instruction, inst + 1, 4);
            instruction[5] = '\0';
            printf("Instruction: %s", instruction);

            int isTime = !strcmp(instruction, "time");
            int isName = !strcmp(instruction, "name");
            int isList = !strcmp(instruction, "list");
            if( isTime || isName) {
                for(char* c = buffer;; c++) {
                    if(*c == '}') {
                        *c = '\0';
                        break;
                    }
                }
                if(isTime) {

                    printf("Server time: %s\n", inst + instLen);
                    fflush(stdout);
                    PressAnyKeyToContinue();
                    stall = FALSE;
                }

                if(isName) {
                    printf("Server name: %s\n", inst + instLen);
                    fflush(stdout);
                    PressAnyKeyToContinue();
                    stall = FALSE;
                }
            } else if (isList){
                printf("Server client list: %s\n", inst + instLen);
                fflush(stdout);
                PressAnyKeyToContinue();
                stall = FALSE;
            } else {
                // other input
                printf("Server instruction: %s", inst);
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
//
// Created by Fenghe Xu on 2019-10-20.
//

#define BUFSIZE 1024
#include "TCPServerUtility.h"
#include "DieWithMessage.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>


void HandleTCPClient(int clntSocket) {
    char buffer[BUFSIZE]; // Buffer for echo string
    int isClosed = 0;

    // send "hello" back to the client before receiving
    char hello_msg[] = "Hello there, what can I do for you?";
    ssize_t numBytesSent = send(clntSocket, hello_msg, strlen(hello_msg), 0);
    if(numBytesSent < 0)
        DieWithSystemMessage("send() failed");

    // Receive message from client
    ssize_t numBytesRcvd = recv(clntSocket, buffer, BUFSIZE, 0);
    if(numBytesRcvd < 0)
        DieWithSystemMessage("recv() failed");
    // printf("buffer after receiving: %s\n", buffer);



    // if(!str)


    char* inst = buffer;
    for(int i = 0; i < strlen(buffer); i++) {
        if(inst[i] < 'a' || inst[i] > 'z') {
            inst[i] = '\0';
            break;
        }
    }
    printf("Instruction received: %s\n", inst);

    if(!strcmp(buffer, "close")) {
        printf("Action: client %d closed\n\n", clntSocket);
        fflush(stdout);
        isClosed = 1;
        close(clntSocket); // Close client socket
        pthread_exit(0);
    }

}
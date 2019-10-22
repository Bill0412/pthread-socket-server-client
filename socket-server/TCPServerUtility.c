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
#include <math.h>
#include <time.h>
#include <unistd.h>

int str2int(char* s, int len)
{
    int res = 0;

    for(int i = 0; i < len; i++) {
        res += ((s[i] - '0') * pow(10, len - 1 - i));
    }

    return res;
}

void HandleTCPClient(int clntSocket) {
    char buffer[BUFSIZE]; // Buffer for echo string
    // send "hello" back to the client before receiving
    char hello_msg[] = "Hello there, what can I do for you?";
    ssize_t numBytesSent = send(clntSocket, hello_msg, strlen(hello_msg), 0);
    printf("Hello Message sent\n");
    fflush(stdout);

    if(numBytesSent < 0)
        DieWithSystemMessage("send() failed");

    // Receive message from client
    int numBytesRcvd;
    for( ; ; ) {
        numBytesRcvd = recv(clntSocket, buffer, BUFSIZE, 0);
        if(numBytesRcvd <= 0) {
            continue;
        }
        char* inst = buffer;

        printf("Instruction received: %s\n", inst);

        // "close"
        if(*inst == 'c') {
            printf("Action: client(%d) closed\n\n", clntSocket);
            fflush(stdout);

            close(clntSocket); // Close client socket
            pthread_exit(0);
        }

        // "time": get time
        if(*inst == 't') {
            // to be modified to dynamic time
            time_t t = time(NULL);
            struct tm *tm = localtime(&t);
            char s[512];
            strftime(s, sizeof(s), "%c", tm);

            char res[512];
            sprintf(res, "{time:%s}", s);

            numBytesSent = send(clntSocket, res, strlen(res), 0);
            if(numBytesSent < 0)
                DieWithSystemMessage("time send() failed");
            printf("bytes sent: %d\n", numBytesSent);

            printf("Action: sent current time [%s] to the client\n", res);
        }

        // "name": get machine name
        if(*inst == 'n') {
            // to be modified to dynamic time
            const int name_limit = 128;
            char name[name_limit];

            gethostname(&name, name_limit);

            char res[256];
            sprintf(res, "{name:%s}", name);

            numBytesSent = send(clntSocket, res, strlen(res), 0);
            if(numBytesSent < 0)
                DieWithSystemMessage("time send() failed");

            printf("Action: sent machine name [%s] to the client\n", name);
        }

        // "list": list all the clients
        if(*inst == 'l') {
            // to be modified to dynamic time
            char list[] = "list";

            numBytesSent = send(clntSocket, list, strlen(list), 0);
            if(numBytesSent < 0)
                DieWithSystemMessage("time send() failed");

           printf("Action: sent client list to the client\n");
        }

        // send
        // example: "send12hello,world"
        if(*inst == 's') {
            // get the client number
            int i = 4 + 1;
            for(; inst[i] <= '9' && inst[i] >= '0'; i++);

            // last digit: i - 1
            int client_id = str2int(inst + 4, i - 4);
            printf("client_id: %d\n", client_id);

            // get the content to send
            char* content = inst + i;

            // filter out the extra tail
            for(char* c = content; ; c++) {
                if(*c == '\\') {
                    *c = '\0';
                    break;
                }
            }

            numBytesSent = send(clntSocket, content, strlen(content), 0);
            if(numBytesSent < 0)
                DieWithSystemMessage("time send() failed");

            printf("Action: sent [%s] to the client(%d)\n", content, client_id);
        }

        // clear the instruction
        printf("Cleared the Instruction, waiting for the next...\n\n");
        inst[0] = '\0';
    }

}
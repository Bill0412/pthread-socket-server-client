//
// Created by Fenghe Xu on 2019-10-21.
//

#include "HandleConnect.h"
#include <stdio.h>
#include <sys/types.h>
#include "DieWithMessage.h"
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <pthread.h>
#include "MsgListener.h"
#include "Globals.h"
int sock;

pthread_t tid;  // thread identifier
pthread_attr_t attr;    // set of thtread attributes


void handleConnect()
{
    // get ip and port from user input
    in_port_t servPort = 0;
    char *servIP = (char *)malloc(sizeof(char) * 100);

#if DEBUG
    servIP = "127.0.0.1";
    servPort = 2881;
#else
    printf("(Recommended Destination: 127.0.0.1:2881)\n");

    printf("Server IP: ");
    fflush(stdout);
    scanf("%s", servIP);

    printf("Connect Port: ");
    fflush(stdout);
    scanf("%hd", &servPort);
#endif

    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    printf("Socket created.\n");
    // Construct the server address structure
    struct sockaddr_in servAddr;    // Server address
    memset(&servAddr, 0, sizeof(servAddr)); // Zero out structure
    servAddr.sin_family = AF_INET;          // IPv4 address family

    // Convert address
    int rtnVal = inet_pton(AF_INET, servIP, &servAddr.sin_addr.s_addr);
    if (rtnVal == 0)
        DieWithUserMessage("inet_pton() failed", "invalid address string");
    else if (rtnVal < 0)
        DieWithSystemMessage("inet_pton() failed");
    servAddr.sin_port = htons(servPort);    // Server port

    // Establish the connection to the echo server
    if (connect(sock, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0)
        DieWithSystemMessage("connect() failed");

    stage = CONNECTED;

    // pthread client listener
    // set the default attributes of the thread
    pthread_attr_init(&attr);

#if DEBUG
    printf("\nsock outside pthread: %d\n", sock);
#endif
    pthread_create(&tid, &attr, msgListener, 0);
    stall = TRUE;
#if DEBUG
    printf("thread created");
#endif
}
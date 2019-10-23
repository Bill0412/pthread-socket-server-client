#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "Practical.h"
#include "ClientList.h"

static const int MAXPENDING = 5;

int main() {
    in_port_t servPort = 2881; // local port: last four digits of Student ID

    // init clientList
    InitClientList();

    // Create socket for incoming connections
    int servSock; // Socket descriptor for server
    if((servSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        DieWithSystemMessage("socket() failed");

    // Construct local address structure
     struct sockaddr_in servAddr;               // local address
     memset(&servAddr, 0, sizeof(servAddr));    // Zero out structure
     servAddr.sin_family = AF_INET;             // IPv4 family
     servAddr.sin_addr.s_addr = htonl(INADDR_ANY);     // Any incoming interface
     servAddr.sin_port = htons(servPort);       // local port

     // Bind to the local address
     if (bind(servSock, (struct sockaddr*) &servAddr, sizeof(servAddr)) < 0)
         DieWithSystemMessage("bind() failed");

     // Make the socket so it will listen for incoming connections
     if (listen(servSock, MAXPENDING) < 0)
         DieWithSystemMessage("listen() failed");

     for (; ; ) {   // Run forever
         pthread_t tid; // thread identifier
         pthread_attr_t attr;   // set of thread attributes

         struct sockaddr_in *ptrClntAddr = malloc(sizeof(struct sockaddr_in)); // Client address
         // Set length of client address structure(in-out parameter)
         socklen_t clntAddrLen = sizeof(*ptrClntAddr);

         // Wait for a client to connect
         int clntSock = accept(servSock, (struct sockaddr *) ptrClntAddr, &clntAddrLen);
         if (clntSock < 0)
             DieWithSystemMessage("accept() failed");

         // When accept succeeds, create a child thread for it
         // set the default attributes of the thread
         pthread_attr_init(&attr);

         // construct the args list
         struct arg_struct *ptrArgs = malloc(sizeof(struct arg_struct));
         ptrArgs->clientAddr = ptrClntAddr;
         ptrArgs->clntSock = clntSock;
         // create the thread
         pthread_create(&tid, &attr, acceptor, (void *) ptrArgs);
     }

    return 0;
}
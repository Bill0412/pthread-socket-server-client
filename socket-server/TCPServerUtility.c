//
// Created by Fenghe Xu on 2019-10-20.
//

#define BUFSIZE 1024
#include "TCPServerUtility.h"

void HandleTCPClient(int clntSocket) {
    char buffer[BUFSIZE]; // Buffer for echo string

    // Receive message from client
    ssize_t numBytesRcvd = recv(clntSocket, buffer, BUFSIZE, 0);
    if(numBytesRcvd < 0)
        DieWithSystemMessage("recv() failed");

    // Send received string and receive again until end of stream
    while (numBytesRcvd > 0) { // 0 indicates end of stream
        // Echo message back to client
        ssize_t numBytesSent = send(clntSocket, buffer, numBytesRcvd, 0);
        if(numBytesSent < 0)
            DieWithSystemMessage("send() failed");
        else if (numBytesSent != numBytesRcvd)
            DieWithUserMessage("send()", "sent unexpected number of bytes");

        // See if there is more data to receive
        numBytesRcvd = recv(clntSocket, buffer, BUFSIZE, 0);
        if(numBytesSent < 0)
            DieWithUserMessage("recv() failed");
    }

    close(clntSocket); // Close client socket
}
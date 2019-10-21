//
// Created by Fenghe Xu on 2019-10-21.
//

#include "UserInterface.h"

#include <stdio.h>
#include "HandleConnect.h"
#include "Globals.h"

/* Declarations */
int stage;
// display functions
void displayDisconnected();
void displayConnected();

// response functions
void responseDisconnected();
void responseConnected();


// handle the functionalities

void handleQuit();
void handleClose();
void handleGetTime();
void handleGetMachineName();
void handleListClients();
void handleSendToClient();

void display()
{
    switch(stage) {
        case DISCONNECTED: displayDisconnected(); break;
        case CONNECTED: displayConnected(); break;
        default: displayConnected(); break;
    }
}

void displayDisconnected()
{
    printf("\n\n");
    fflush(stdin);
    printf("Welcome using the socket client!\n");
    printf("[c] connect to a server\n");
    printf("[q] quit\n");
    printf("\tPlease choose between the options. (Enter 'c' or 'q') ");
    fflush(stdout);
}

void displayConnected()
{
    printf("\n\n");
    fflush(stdin);
    printf("[c] (c)onnect to a server\n");
    printf("[x] close the connection\n");
    printf("[t] get the (t)ime on the server\n");
    printf("[n] get the server machine (n)ame\n");
    printf("[l] (l)ist all the clients connected to the server\n");
    printf("[s] Instruct the server to (s)end to the clients\n");
    printf("[q] (q)uit\n");
    printf("\tPlease choose among the options. (Enter 'q' for quit) ");
    fflush(stdout);
}


void responseDisconnected()
{
    switch(getchar()) {
        case 'c': handleConnect(); break;
        case 'q': handleQuit(DISCONNECTED); break;  // quit when disconnected
        default: displayDisconnected();
    }
}

void responseConnected()
{
    switch(getchar()) {
        case 'c': handleConnect(); break;
        case 'x': handleClose(); break;
        case 't': handleGetTime(); break;
        case 'n': handleGetMachineName(); break;
        case 'l': handleListClients(); break;
        case 's': handleSendToClient(); break;
        case 'q': handleQuit(); break;  // quit when connected
    }
}


void response()
{
    switch(stage) {
        case DISCONNECTED: responseDisconnected(); break;
        case CONNECTED: responseConnected(); break;
        default: responseDisconnected(); break;
    }
}

void handleQuit()
{

}

void handleClose()
{

}

void handleGetTime()
{

}


void handleGetMachineName()
{

}

void handleListClients()
{

}

void handleSendToClient()
{

}
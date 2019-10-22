//
// Created by Fenghe Xu on 2019-10-22.
//

#ifndef SOCKET_CLIENT_GLOBALS_H
#define SOCKET_CLIENT_GLOBALS_H
#include <pthread.h>

#define DISCONNECTED 0
#define CONNECTED 1
#define TRUE 1
#define FALSE 0

extern int stage;
extern int stall;
extern int quit;
extern int sock;


// pthread client listener
extern pthread_t tid;  // thread identifier
extern pthread_attr_t attr;    // set of thtread attributes

#if 0
int connected()
{
    int prevStage = stage;

    stage = CONNECTED;

    return prevStage;
}

int disconnected()
{
    int prevStage = stage;

    stage = DISCONNECTED;

    return prevStage;
}
#endif
#endif //SOCKET_CLIENT_GLOBALS_H

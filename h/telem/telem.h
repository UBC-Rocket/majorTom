/*
Header file for Telemetry board
*/

#ifndef TELEM_H
#define TELEM_H

#include <stdbool.h>
#include <stdint.h>
#include <time.h> //for time_t


#define SENSOR_COUNT 16
#define LISTEN_QUANTUM 500
#define BUFFER_SIZE 8
typedef double canbus_t;



/* Hardware-dependent functions */
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void initSend(int* fd, struct sockaddr_un* addr);


/* Hardware-independent functions */
#include "amessage.pb.h"
#include "pb_encode.h"
#include "general.h"


extern int main(void);

//sets up registers, attempt to link to ground station
status_t telemInit();

//sets up registers, attempt to link to ground station
status_t telemWrite();

//connect to ground station
status_t telEstLink();

status_t telCollect();

//Main logic is here
status_t telem(void);

status_t listenOnBus(AMessage* telemDataBuffer);

status_t pbPackage(pb_byte_t* targetBuffer, size_t targetBufferSize, AMessage* data);

#endif

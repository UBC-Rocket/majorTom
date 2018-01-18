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

status_t initSend(int* fd, struct sockaddr_un* addr);
status_t canListen(int* id, canbus_t* canbusData);

/* Hardware-independent functions */
#include "amessage.pb.h"
#include "pb_encode.h"
#include "general.h"

extern int main(void);

//sets up registers, attempt to link to ground station
status_t telemInit();


status_t listenOnBus(AMessage* telemDataBuffer);

status_t pbPackage(pb_byte_t* targetBuffer, pb_ostream_t* stream, size_t targetBufferSize, AMessage* data);

status_t pbSend(pb_ostream_t* stream, pb_byte_t buffer[AMessage_size]);

#endif

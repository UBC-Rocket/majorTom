/*
Header file for Telemetry board
*/

#ifndef TELEM_H
#define TELEM_H

/* Hardware-dependent functions */

<<<<<<< HEAD
/* Hardware-independent functions */
extern int main(void);
=======
#include <stdbool.h>
#include <stdint.h>
#include <time.h> //for time_t


#define SENSOR_COUNT 16
#define LISTEN_QUANTUM 500
#define BUFFER_SIZE 8
typedef double canbus_t; //datatype used internally by the CAN Bus

typedef struct canbusData
{
	bool isValid;
	time_t timestamp;
	canbus_t data[SENSOR_COUNT];
} cbd_t;


//Define helper functions here


//Entry point. Alternative versions based on hardware.
int main(void);
>>>>>>> eb30bf7... work in progress towards telem mocking

#endif

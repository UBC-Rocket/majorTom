/*
Main implementation of Telemetry board
*/

//TODO stub out algorithms needed for testing telem board
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <pb/amessage.pb.h>
#include "telem/telem.h"

//returns time in seconds
time_t getTimeSec() {
	struct timespec spec;
	clock_gettime(CLOCK_REALTIME, &spec);
	return spec.tv_sec;
}

status_t telemInit() {
	printf("telemInit()\n");
	printf("setting up registers\n");

	printf("calling up telEstLink()");
	printf("leaving telemInit()\n");
}

status_t telEstLink() {
	printf("telEstLink()\n");
	printf("set frequency\n");
	printf("set link speed\n");
	printf("using bsp functions to establish link\n");
	printf("attempt to negotiate\n"); //negotiating is for terrorists!
	bool status = rand() % 2 == 0; //should call real radio link connection

	if (status) { //do some sort of check for status code
		return STATUS_OK;
	} else {
		return STATUS_ERROR;
	}

	printf("leaving telEstLink()\n");
}


status_t pbPackage(pb_byte_t *pBuf, cbd_t data) {
	AMessage msg = AMessage_init_default; //model for data packet

	for (int i = 0; i < 4; i++) {
		//generate protobuf message
		msg.a = i;
		msg.b = i + 1;
		pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer)); //declare the output buffer to be used
		bool status = pb_encode(&stream, AMessage_fields, &msg); //encode message to the buffer
		if (!status) {
			printf("Encoding failed: %s\n", PB_GET_ERROR(&stream));
			return STATUS_ERROR;
		}
	}
}

int main() {
	telemInit();
	telEstLink();

	while (true) {
		//get raw canbus data
		cbd_t data;
		listenOnBus(&data);

		//package canbus data as protobuf
		pb_byte_t pbBuf[AMessage_size]; // Buffer to store serialized data
		pbPackage(pbBuf, data);


	}

	return 0;
}


//function stub
status_t canListen(int *id, canbus_t *canbusData) {
	if (rand() % 2 == 0) //randomly return data for testing purposes
	{
		*id = 1;
		*canbusData = 10;
	} else {
		*id = 2;
		*canbusData = 20;
	}
	return STATUS_OK;
}

//listens on the bus and updates telemDataBuffer with stuff from CAN bus until timeout
//or received data from SENSOR_COUNT unique sensors
//returns STATUS_OK if we receive data,
status_t listenOnBus(cbd_t *telemDataBuffer) {
	bzero(telemDataBuffer, sizeof(cbd_t));
	int uniqueSourceCount = 0;
	for (int i = 0; i < LISTEN_QUANTUM && uniqueSourceCount < SENSOR_COUNT; i++) {
		int senderID;
		canbus_t sensorReading;
		canListen(&senderID, &sensorReading);

		//TODO: check if sensors ever return null (or else uniqueSourceCount is useless)
		if (telemDataBuffer->data[senderID] == NULL) {
			uniqueSourceCount++;
		}
		telemDataBuffer->data[senderID] = sensorReading;
	}

	if (uniqueSourceCount > 0) {
		telemDataBuffer->isValid = true;
		telemDataBuffer->timestamp = getTime();
		return STATUS_OK;
	}

	return STATUS_NO_DATA;
}

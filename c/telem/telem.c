/*
Hardware-independent functions from telem.h
*/

//TODO stub out algorithms needed for testing telem board
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <pb/amessage.pb.h>
#include "telem/telem.h"
#include "telem/telemFunc.h"


status_t pbPackage(pb_byte_t* pBuf, cbd_t data) {
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

/**
 * @brief Telementry board routine - hardware-independent implementation
 * @return Status.
 */
int main() {
	telemInit();

	while (true) {
		//get raw canbus data
		cbd_t data;
		listenOnBus(&data);

		//package canbus data as protobuf
		pb_byte_t pbBuf[AMessage_size]; // Buffer to store serialized data
		pbPackage(pbBuf, data);

	}
}


//function stub
status_t canListen(int* id, canbus_t* canbusData) {
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
status_t listenOnBus(cbd_t* telemDataBuffer) {
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

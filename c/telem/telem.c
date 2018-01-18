/*
Hardware-independent functions from telem.h
*/

//TODO stub out algorithms needed for testing telem board
#include <stdio.h>
#include "shared/utils.h" //for tsprintf
#include "telem.h"

//const pb_field_t AMessage_fields[3]; //fixme: not sure why includes are broken for makefile

/**
 * @brief listens on the bus and updates telemDataBuffer with stuff from CAN bus until timeout
 * or received data from SENSOR_COUNT amount of unique sensors
 * @param telemDataBuffer: struct used to store the received canbus data for protobuf
 * @return STATUS_OK if we receive data

 */
#define BAD_FLAG 0
status_t listenOnBus(AMessage* telemDataBuffer) {
//	bzero(telemDataBuffer, sizeof(AMessage_size));
	int uniqueSourceCount = 0;
	for (int i = 0; i < LISTEN_QUANTUM && uniqueSourceCount < SENSOR_COUNT; i++) {
		int senderID;
		canbus_t sensorReading;
		canListen(&senderID, &sensorReading);

		//TODO: check if sensors ever return null (or else uniqueSourceCount is useless)
		if (telemDataBuffer->data[senderID] == BAD_FLAG) {
			uniqueSourceCount++;
		}
		telemDataBuffer->data[senderID] = sensorReading;
	}

	if (uniqueSourceCount > 0) {
		time_t time; getTimeSec(&time);
		telemDataBuffer->timestamp = time;
		telemDataBuffer->data_count = uniqueSourceCount;
		return STATUS_OK;
	}

	return STATUS_NO_DATA;
}


/**
 * @brief packages a protobuf message into a payload stored in targetBuffer
 * @note expects data->data_count to be set to the correct number of valid fields used. Will not send elements beyond data_count
 * @param targetBuffer: buffer to store the protobuf payload
 * @param stream: protobuf stream used to generate the payload
 * @param targetBufferSize: the size of the buffer for protobuf to store its payload
 * @param data: the input data struct to convert into a protobuf payload
 * @return Status code
 */
status_t pbPackage(pb_byte_t* targetBuffer, pb_ostream_t* stream, size_t targetBufferSize, AMessage* data) {
	*stream = pb_ostream_from_buffer(targetBuffer, targetBufferSize);
	bool status = pb_encode(stream, AMessage_fields, data);
	if (!status) {
		tsprintf("Encoding failed: %s\n", PB_GET_ERROR(stream));
		return STATUS_ERROR;
	}

	return STATUS_OK;
}

/**
 * @brief Telemetry board routine - hardware-independent implementation
 * @return Status.
 */
int main() {
	printf("started\n");
	telemInit();

	while (true) { //main loop to receive and send data
		//get raw canbus data
		AMessage data = AMessage_init_default;
		listenOnBus(&data);

		//package canbus data as protobuf
		pb_byte_t pbBuf[AMessage_size]; // Buffer to store serialized data
		pb_ostream_t stream; //stream to send to our recipient
		pbPackage(pbBuf, &stream, AMessage_size, &data);
		pbSend(&stream, pbBuf);
//		printf("running\n");
	}
}
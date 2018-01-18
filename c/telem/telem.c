/*
Hardware-independent functions from telem.h
*/

//TODO stub out algorithms needed for testing telem board
#include <stdio.h>
#include "shared/utils.h" //for tsprintf
#include "telem.h"

//const pb_field_t AMessage_fields[3]; //fixme: not sure why includes are broken for makefile

/**
 * @brief sets the ith bit in validDataIndexes to track which sensors sent useful data (0 based)
 * @param telemData: struct used to store the received canbus data for protobuf
 * @param senderID: the id of the sensor that sent the data
 */
void setValidIndex(AMessage* telemDataBuffer, int senderID) {
	telemDataBuffer->validDataIndexes |= 1 << senderID;
}

/**
 * @brief listens on the bus and updates telemDataBuffer with stuff from CAN bus until timeout
 * or received data from SENSOR_COUNT amount of unique sensors
 * @param telemData: struct used to store the received canbus data for protobuf
 * @return STATUS_OK if we receive data
 */
status_t listenOnBus(AMessage* telemData) {
	bzero(telemData, AMessage_size); //clear the buffer for reuse
	for (int i = 0; i < LISTEN_QUANTUM; i++) {
		int senderID;
		canbus_t sensorReading;
		if (canListen(&senderID, &sensorReading) == STATUS_OK) {
			setValidIndex(telemData, senderID);
			telemData->data[senderID] = sensorReading;
		}
	}

	if (telemData->validDataIndexes == 0) {
		return STATUS_NO_DATA;
	}

	time_t time;
	getTimeSec(&time);
	telemData->timestamp = time;
	telemData->data_count = sizeof(telemData->data) / sizeof(telemData->data[0]); //hard coded for now
	return STATUS_OK;
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
	if (telemInit() != STATUS_OK) {
		tsprintf("Error listening on bus\n");
	}

	while (true) { //main loop to receive and send data
		//get raw canbus data
		AMessage data = AMessage_init_default;
		if (listenOnBus(&data) != STATUS_OK) {
			tsprintf("Error listening on bus\n");
		}

		pb_byte_t pbBuf[AMessage_size]; // Buffer to store serialized data
		pb_ostream_t stream; //stream to send to our recipient

		if (pbPackage(pbBuf, &stream, AMessage_size, &data) != STATUS_OK) {
			tsprintf("Error packaging into protobuf\n");
		}

		if (pbSend(&stream, pbBuf) != STATUS_OK) {
			tsprintf("Error sending protobuf payload \n");
		}

//		printf("running\n");
	}
}
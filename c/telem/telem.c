/*
Hardware-independent functions from telem.h
*/

//TODO stub out algorithms needed for testing telem board
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "telem.h"

const pb_field_t AMessage_fields[3]; //fixme: not sure why includes are broken

//generates protobuf message targetBuffer
//expects data_count to be set as it only transmits however many elements you specify
status_t pbPackage(pb_byte_t* targetBuffer, size_t targetBufferSize, AMessage* data) {
	pb_ostream_t stream = pb_ostream_from_buffer(targetBuffer, targetBufferSize);
	bool status = pb_encode(&stream, AMessage_fields, data);
	if (!status) {
		printf("Encoding failed: %s\n", PB_GET_ERROR(&stream));
		return STATUS_ERROR;
	}

	return STATUS_OK;
}



/**
 * @brief Telementry board routine - hardware-independent implementation
 * @return Status.
 */

int main() {
	printf("started\n");
	telemInit();

	while (true) {
		//get raw canbus data
		AMessage data;
		listenOnBus(&data);

		//package canbus data as protobuf
		pb_byte_t pbBuf[AMessage_size]; // Buffer to store serialized data
		pbPackage(pbBuf, AMessage_size, &data);
		printf("running\n");
	}
}
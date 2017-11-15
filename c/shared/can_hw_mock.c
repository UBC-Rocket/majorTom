/*
Mock implementation of CAN bus library's hardware-dependent portion
*/

#include <stdio.h>
#include <stdint.h>

#include <shared/can.h>
#include <shared/init.h>
#include <general.h>

//Mock implementations of functions from can.h

/**
 * @brief A mock implementation of writing a message to the CAN bus.
 * @param id The identifier used to identify where the message is coming from.
 * @param data The data to send.
 * @return Status.
 */
status_t canWrite(can_id_t id, uint64_t data)
{
	fprintf(fp_can_write, "%lu\n%lu\n", id, data);

	return STATUS_OK;
}

/**
 * @brief A mock implementation of reading a message from the CAN bus.
 * @param *id A pointer to store the message identifier.
 * @param *data A pointer to store the message data.
 * @return Status.
 */
status_t canRead(can_id_t *id, uint64_t *data)
{
	fscanf(fp_can_read, "%lu%lu", id, data);

	//Same functionality as the CAN controller filters and masks.
	if (*id == CAN_ALWAYS_PROCESS) {
		printf("CAN message processed!\n");
		return STATUS_OK;
	}

	printf("CAN message ignored!\n");
	return STATUS_CAN_FILTERED;
}

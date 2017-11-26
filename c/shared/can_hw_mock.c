/*
Mock implementation of CAN bus library's hardware-dependent portion
*/

#include <stdint.h>
#include <stdio.h>

#include <shared/can.h>
#include <general.h>
#include <shared/mock_utils.h>

/* Mock implementations of functions from can.h */

/**
 * @brief A mock implementation of writing a message to the CAN bus.
 * @param id The identifier used to identify where the message is coming from.
 * @param data The data to send.
 * @return Status.
 */
status_t canWrite(can_id_t id, uint64_t data)
{
	tsprintf("Writing CAN message to file.\n");
	if (fprintf(fp_can_write, "%lu, %lu\n", id, data) <= 0) {
		tsprintf("Error writing message to file.\n");
		return STATUS_ERROR;
	}

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
	tsprintf("Reading CAN message from file.\n");
	if (fscanf(fp_can_read, "%lu, %lu\n", id, data) != 2) {
		tsprintf("Error reading message from file.\n");
		return STATUS_ERROR;
	}

	/* Same functionality as the CAN controller filters and masks. */
	if (*id == CAN_ALWAYS_PROCESS) {
		tsprintf("CAN message processed!\n");
		return STATUS_OK;
	}

	tsprintf("CAN message ignored!\n");
	return STATUS_CAN_FILTERED;
}

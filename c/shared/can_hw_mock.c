/*
Implementations of functions from can.h for Mock hardware
*/

#include <stdint.h>
#include <stdio.h>

#include <general.h>
#include <can.h>

#include <utils.h>

/* File pointers for input and output data generated by test scripts */
static FILE *fp_can_args = NULL;
static FILE *fp_can_write;
static FILE *fp_can_read;

/**
 * @brief Initialization for CAN bus - mock version (opens automatically-generated files)
 * @return Status.
 */
extern status_t canInit(void)
{
	tsprintf("Initializing mock CAN bus.\n");

	fp_can_args = fopen("./test-can/can_test_args.txt", "r");
	if (fp_can_args == NULL) {
		tsprintf("Failed to open CAN test args file.\n");
		return STATUS_ERROR;
	}

	char can_data_filename[30];
	char can_read_data[30];
	char can_write_data[30];

	if (fscanf(fp_can_args, "%s\n", can_data_filename) != 1) {
		tsprintf("Error reading filename from can_test_args.txt.\n");
		return STATUS_ERROR;
	}

	sprintf(can_read_data, "%s.csv", can_data_filename);
	fp_can_read = fopen(can_read_data, "r");
	if (fp_can_read == NULL) {
		tsprintf("Failed to open CAN read data file.\n");
		return STATUS_ERROR;
	}

	sprintf(can_write_data, "%s_actual.csv", can_data_filename);
	fp_can_write = fopen(can_write_data, "w+");
	if (fp_can_write == NULL) {
		tsprintf("Failed to open CAN write data file.\n");
		return STATUS_ERROR;
	}
}

/**
 * @brief Write a message to the CAN bus - mock implementation (writes to a file)
 * @param id The identifier used to identify where the message is coming from.
 * @param data The data to send.
 * @return Status.
 */
extern status_t canWrite(can_id_t id, uint64_t data)
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
extern status_t canRead(can_id_t *id, uint64_t *data)
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

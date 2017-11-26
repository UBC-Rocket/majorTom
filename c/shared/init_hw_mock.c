/*
Mock implementation of Initialization library
*/

#include <stdio.h>

#include <shared/init.h>
#include <general.h>
#include <shared/mock_utils.h>

/* Global */
FILE *fp_can_write = NULL;
FILE *fp_can_read = NULL;

/* Local */
FILE *fp_can_args = NULL;

/* Mock implementations of functions from init.h */

/**
 * @brief Initialization for CAN bus mocking.
 * @return Status.
 */
status_t initCanMock(void)
{
	tsprintf("Initializing mock CAN bus.\n");

	fp_can_args = fopen("./test-can/can_test_args.txt", "r");
	if (fp_can_args == NULL) {
		tsprintf("Failed to open CAN test args file.\n");
		return STATUS_ERROR;
	}

	return STATUS_OK;
}

/**
 * @brief Initialization for CAN bus testing using generated data.
 * @return Status.
 */
status_t initCanTest(void)
{
	char can_data_filename[30];
	char can_read_data[30];
	char can_write_data[30];

	tsprintf("Initializing mock CAN bus test.\n");

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

	return STATUS_OK;
}

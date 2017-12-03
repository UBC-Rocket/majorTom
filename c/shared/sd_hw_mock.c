/*
Implementations of functions from sd.h for Mock hardware
*/
#include <stdio.h>

#include <general.h>
#include <sd.h>

#include <init.h>
#include <utils.h>

static FILE *file_sd;

/*
@brief Initialization for SD log - mock implementation (opens a file)
@param Array of doubles
@param Length of double array.
@return status_t
*/
extern status_t sdInit(void)
{
	file_sd = fopen("./test-io/sd_file.txt", "w+");
	if (file_sd == NULL) {
		return STATUS_ERROR;
	} else {
		return STATUS_OK;
	}
}

/*
@brief Writes a double to the SD card log - mock implementation (writes to a file)
@param Array of doubles
@param Length of double array.
@return status_t
*/
extern status_t sdWriteDouble(double output[], int length)
{
	time_t timestamp;
	getTimeSec(&timestamp);
	fprintf(file_sd, "[%ld] ", timestamp);
	for (int i = 0; i < length; i++) {
		fprintf(file_sd, "%lf ", output[i]);
	}
	fprintf(file_sd, "\n");

	return STATUS_OK;
}

/*
@brief Writes a string to the SD card log - mock implementation (writes to a file)
@param String
@return status_t
*/
extern status_t sdWriteString(char output[])
{
	time_t timestamp;
	getTimeSec(&timestamp);
	fprintf(file_sd, "[%ld] %s\n", timestamp, output);
	return STATUS_OK;
}

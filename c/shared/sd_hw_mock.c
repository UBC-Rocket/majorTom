/*
Mock implementation of IO SD card library
*/

#include <shared/sd.h>
#include <shared/init.h>
#include <shared/mock_utils.h>

/*
@brief Mock implementation of writing doubles to a SD file log.
@param Array of doubles
@param Length of double array.
@return status_t
*/
status_t sdWriteDouble(double output[], int length) {
	time_t timestamp = getTimeSec();
	fprintf(file_sd, "[%ld] ", timestamp);
	for (int i = 0; i < length; i++) {
		fprintf(file_sd, "%lf ", output[i]);
	}
	fprintf(file_sd, "\n");

	return STATUS_OK;
}

/*
@brief Mock implementation of writing a string to a SD file log.
@param String
@return status_t
*/
status_t sdWriteString(char output[]) {
	time_t timestamp = getTimeSec();
	fprintf(file_sd, "[%ld] %s\n", timestamp, output);
	return STATUS_OK;
}

/*
Mock implementation of IO SD card library
*/

#include <shared/io_sd.h>
#include <shared/init.h>

/*
@brief Mock implementation of writing doubles to a SD file log.
@param Array of doubles
@param Length of double array.
@return status_t
*/
status_t sdWriteDouble(double[] output, int length) {
	fprintf(file_sd, "[TIMESTAMP] ");
	for (int i = 0; i < length; i++) {
		fprintf(file_sd, "%d", output[i]);
	}
	fprintf(file_sd, "\n");

	return STATUS_OK;
}

/*
@brief Mock implementation of writing a string to a SD file log.
@param String
@return status_t
*/
status_t sdWriteString(char[] output) {
	fprintf(file_sd, "[TIMESTAMP] %s\n", output);
	return STATUS_OK;
}

//Add read function.

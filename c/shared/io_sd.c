/*
Mock implementation of IO SD card library
*/

#include <shared/io_sd.h>
#include <shared/init.h>

/*


*/
status_t io_sdWrite(double[] output, int length) {
	fprintf(file_sd, "[TIMESTAMP] "); //Add timestamp to print.
	for (int i = 0; i < length; i++) {
		fprintf(file_sd, "%d", output[i]);
	}
	fprintf(file_sd, "\n");
}

//Add read function.

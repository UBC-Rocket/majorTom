/*
Mock implementation of Initialization library
*/

#include <shared/init.h>

FILE *file_sd;

//Mock implementations of functions from init.h

status_t initSDFile(void) {
	file_sd = fopen("./sd_file.txt", "w+");
	if (file_sd == NULL) {
		return STATUS_ERROR;
	} else {
		return STATUS_OK;
	}
}

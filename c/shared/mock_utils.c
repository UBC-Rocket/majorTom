/*
Implementations of mocking utilities
*/

#include <stdio.h>

#include "mock_utils.h"

status_t tsprintf(const char *format, ...)
{
	printf("[%s] ", STUFF);
	printf(format, format + sizeof(char *));
	return STATUS_OK;
}
/*
Implementations of mocking utilities
*/


#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <math.h>
#include <time.h>

#include <general.h>
#include "mock_utils.h"


status_t tsprintf(const char* format, ...)
{
	/* Get the current time */
	struct timespec spec;
	clock_gettime(CLOCK_REALTIME, &spec);
	uint64_t ms = round(spec.tv_nsec / 1.0e6); // Milliseconds
	time_t s = spec.tv_sec;  // Seconds

	/* Print the timestamp */
	printf("[%ld.%ld] ", s, ms);

	/* Print the given message */
	va_list args;
	va_start(args, format);
	vprintf(format, args);
	va_end(args);

	/* Success! */
	return STATUS_OK;
}
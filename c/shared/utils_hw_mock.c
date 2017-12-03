/*
Implementations of functions from utils.h for Mock hardware
*/


#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <math.h>
#include <time.h>

#include <general.h>
#include <utils.h>


/*
@brief Gets the current time - mock implementation (Uses the system clock)
@param time_t *
@return status_t
*/
extern status_t getTimeSec(time_t *the_time)
{
	struct timespec spec;
	clock_gettime(CLOCK_REALTIME, &spec);
	*the_time = spec.tv_sec;
	return STATUS_OK;
}

/*
@brief Reports a format string with a timestamp - mock implementation (Uses the system clock and prints to stdout)
@param char *
@param ...
@return status_t
*/
extern status_t tsprintf(char* format, ...)
{
	/* Get the current time */
	struct timespec spec;
	clock_gettime(CLOCK_REALTIME, &spec);
	uint64_t time_millis = round(spec.tv_nsec / 1.0e6);
	time_t time_sec = spec.tv_sec;

	/* Print the timestamp */
	printf("[%ld.%ld] ", time_sec, time_millis);

	/* Print the given message */
	va_list args;
	va_start(args, format);
	vprintf(format, args);
	va_end(args);

	/* Success! */
	return STATUS_OK;
}

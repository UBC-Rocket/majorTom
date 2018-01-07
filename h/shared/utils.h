/*
Header file for mocking utilities
*/

#ifndef MOCK_UTILS_H
#define MOCK_UTILS_H

#include <general.h>
#include <time.h>
#include <stdint.h>

/* Hardware-dependent functions */
extern status_t getTimeSec(time_t *the_time);
extern status_t tsprintf(char *format, ...);
extern status_t delay(uint64_t milliseconds);

/* Hardware-independent functions */

#endif

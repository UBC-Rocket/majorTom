/*
Header file for mocking utilities
*/

#ifndef MOCK_UTILS_H
#define MOCK_UTILS_H

#include <general.h>
#include <time.h>

//returns time in seconds
time_t getTimeSec();

status_t tsprintf(const char *format, ...);


#endif

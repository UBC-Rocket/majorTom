/*
Implementations of functions from init.h for Mock hardware
*/

#include <general.h>
#include <init.h>

#include <utils.h>

/**
 * @brief Initialization for hardware platform - mock implementation (does nothing)
 * @return Status.
 */
extern status_t platformInit()
{
	return STATUS_OK;
}
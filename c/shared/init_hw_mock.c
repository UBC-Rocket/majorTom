/*
Mock implementation of Initialization library
*/

#include <stdio.h>

#include <shared/init.h>

FILE *fp_can_write;
FILE *fp_can_read;

//Mock implementations of functions from init.h

/**
 * @brief Initialization for CAN bus mocking.
 */
void initCanMock(void)
{
	fp_can_write = fopen("./can_data_write.txt", "w+");
	fp_can_read = fopen("./can_data_read.txt", "r");
}

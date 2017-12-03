/*
Header file for Board initialization library
*/

#ifndef INIT_H
#define INIT_H

#include <stdio.h>
#include <general.h>

extern FILE *file_sd;

/* Initialization functions */
status_t initSDFile(void);

status_t initCanMock(void);
status_t initCanTest(void);

#endif

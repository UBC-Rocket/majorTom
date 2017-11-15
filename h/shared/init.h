/*
Header file for Board initialization library
*/

#ifndef INIT_H
#define INIT_H

#include <stdio.h>

extern FILE *fp_can_write;
extern FILE *fp_can_read;

//Initialization functions go here
void initCanMock(void);

#endif

/*
Header file for Telemetry board
*/

#ifndef TELEM_H
#define TELEM_H

#include <general.h>
#include <shared/init.h>
#include <shared/gpio.h>
#include <shared/can.h>

//Define helper functions here

//Main logic is here
status_t telem(void);

//Entry point. Alternative versions based on hardware.
int main(void);

#endif

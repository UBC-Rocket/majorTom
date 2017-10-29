/*
Header file for Apogee Detection board
*/

#ifndef APDEC_H
#define APDEC_H

#include <shared/init.h>
#include <shared/gpio.h>
#include <shared/can.h>

//Define helper functions here

//Main logic is here
int apdec(void);

//Entry point. Alternative versions based on hardware.
int main(void);

#endif

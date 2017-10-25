/*
Header file for Power board
*/

#ifndef POWER_H
#define POWER_H

#include <shared/init.h>
#include <shared/gpio.h>
#include <shared/can.h>

//Define helper functions here

//Main logic is here
int power(void);

//Entry point. Alternative versions based on hardware.
int main(void);

#endif

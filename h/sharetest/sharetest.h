/*
Header file for Shared Library Test board
*/

#ifndef SHARETEST_H
#define SHARETEST_H

#include <general.h>
#include <shared/init.h>
#include <shared/gpio.h>
#include <shared/can.h>

//Define helper functions here

//Main logic is here
status_t sharetest(void);

//Entry point. Alternative versions based on hardware.
int main(void);

#endif

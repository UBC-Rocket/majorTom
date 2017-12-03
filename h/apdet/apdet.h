/*
Header file for Apogee Detection board
*/

#ifndef APDEC_H
#define APDEC_H

#include <general.h>
#include <shared/init.h>
#include <shared/gpio.h>
#include <shared/can.h>

#define APDET_STATE_STANDBY           	0
#define APDET_STATE_POWERED_ASCENT    	1
#define APDET_STATE_COASTING          	2
#define APDET_STATE_TEST_APOGEE       	3
#define APDET_STATE_DEPLOY_DROGUE     	4
#define APDET_STATE_DEPLOY_PAYLOAD    	5
#define APDET_STATE_INITIAL_DESCENT   	6
#define APDET_STATE_DEPLOY_MAIN       	7
#define APDET_STATE_FINAL_DESCENT     	8
#define APDET_STATE_LANDED            	9

#define SIM_LAUNCH_ACCEL 			40 /* 40 is old value, ask Ollie assuming sims are accurate, > 40 */
#define SIM_BURNOUT_ACCEL_DELTA		4  /* 40 is old value, ask Ollie */

#define NUM_CHECKS          		5  /* each condition has to pass 5 times */
#define NUM_WRITE_ATTEMPTS  		5  /* 5 is temp value, tbd from testing */


void detect_launch(void); /* transition from STANDBY to POWERED_ASCENT */
void detect_burnout(void); /* transition from POWERED_ASCENT to COASTING */
/* involve time to make sure / as a backup? data is not stable at this point */
void coasting_to_test_apogee(void); /* transition from COASTING to TEST_APOGEE */
void test_apogee(void); /* transition from TEST_APOGEE to DEPLOY DROGUE */
void deploy_drogue(void); /* actually deploys the drogue, then transitions from DEPLOY_DROGUE to DEPLOY_PAYLOAD */
void deploy_payload(void); /* actually deploys the payload, then transitions from DEPLOY_PAYLOAD to INITIAL_DESCENT */
void detect_main_alt(float curr_altitude); /* transitions from INITIAL_DESCENT to DEPLOY_MAIN */
void deploy_main(void); /* actually deploys the main parachute, then transitions from DEPLOY_MAIN to FINAL_DESCENT */
void final_descent(void); /* transitions from FINAL_DESCENT to LANDED */

#endif

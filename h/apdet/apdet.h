/*
Header file for Apogee Detection board
*/

#ifndef APDET_H
#define APDET_H

#include <general.h>

#define APDET_STATE_STANDBY           	0
#define APDET_STATE_POWERED_ASCENT    	1
#define APDET_STATE_COASTING          	2
#define APDET_STATE_DEPLOY_DROGUE     	3
#define APDET_STATE_DEPLOY_PAYLOAD    	4
#define APDET_STATE_INITIAL_DESCENT   	5
#define APDET_STATE_DEPLOY_MAIN       	6
#define APDET_STATE_FINAL_DESCENT     	7
#define APDET_STATE_LANDED            	8

#define SIM_LAUNCH_ACCEL 			   40 /* 40 is old value, ask Ollie assuming sims are accurate, > 40 */
#define SIM_BURNOUT_ACCEL_DELTA		    4  /* 40 is old value, ask Ollie */

#define NUM_CHECKS          		    5  /* each condition has to pass 5 times */
#define NUM_WRITE_ATTEMPTS  		    5  /* 5 is temp value, tbd from testing */

/* Hardware-dependent functions */
extern status_t deploy_drogue();
extern status_t deploy_payload();
extern status_t deploy_main();

/* Hardware-independent functions */

extern int main(void);

#endif

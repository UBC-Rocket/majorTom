/*
Main implementation of Apogee Detection board
*/

#include <apdet.h>
#include <shared/can.h>


void detect_launch(void)
{
	/* detects giant spike in acceleration 
	return when we've seen 5 positive accelerations in a row
	then transitions to powered ascent state */
	int launch_count = 0;
	
	while (launch_count < NUM_CHECKS) { 

		can_id_t can_id; /* canRead stores data in these two variables, takes them as parameters */
		float can_msg;
		status_t retval = canRead(&can_id, (uint64_t *) &can_msg); /* read from CAN */
		if (retval != STATUS_OK || can_id != CAN_ID_SENSOR_ACCEL_Z) { /* check status is okay and id is what we want */
			continue;
		}

		if (can_msg >= SIM_LAUNCH_ACCEL) { /* only ACCEL_Z */
			launch_count++;
		} else {
			launch_count = 0; /* ensures "in a row" */
		}
	}

	status_t retval = STATUS_ERROR;
	for (int i = 0; i < NUM_WRITE_ATTEMPTS && retval != STATUS_OK; i++) {
		retval = canWrite(CAN_ID_APDET_STATE, APDET_STATE_POWERED_ASCENT);
	}
}

void detect_burnout(void)
{
	/* giant drop in acceleration, max velocity (baby delay)
	return when we've seen 5 negative accelerations in a row
	then transitions to coasting state */
	int burnout_count = 0;
	float prev_accel = 0;
	float accel = 0;

	while (burnout_count < NUM_CHECKS) {

		can_id_t can_id;
		float can_msg;
		status_t retval = canRead(&can_id, (uint64_t *) &can_msg;); /* read from CAN */
		if (retval != STATUS_OK || can_id != CAN_ID_SENSOR_ACCEL_Z) {
			continue;
		}

		prev_accel = accel;
		accel = can_msg;

		if ((prev_accel - accel) >= SIM_BURNOUT_ACCEL_DELTA) {
			burnout_count++;
		} else {
			burnout_count = 0; /* ensures "in a row" */
		}
	}

	status_t retval = STATUS_ERROR;
	for (int i = 0; i < NUM_WRITE_ATTEMPTS && retval != STATUS_OK; i++) {
		retval = canWrite(CAN_ID_APDET_STATE, APDET_STATE_COASTING);
	}
}

void coasting_to_test_apogee(void)
/* is it necessary to have coasting and apogee testing in different states?
maybe it's so that there isn't as much computation when it's far from the apogee? */
{
	/* do stuff */

	status_t retval = STATUS_ERROR;
	for (int i = 0; i < NUM_WRITE_ATTEMPTS && retval != STATUS_OK; i++) {
		retval = canWrite(CAN_ID_APDET_STATE, APDET_STATE_TEST_APOGEE);
	}

}

void test_apogee(void)
{
	/* do stuff */

	status_t retval = STATUS_ERROR;
	for (int i = 0; i < NUM_WRITE_ATTEMPTS && retval != STATUS_OK; i++) {
		retval = canWrite(CAN_ID_APDET_STATE, APDET_STATE_DEPLOY_DROGUE);
	}
}

void deploy_drogue(void)
{
	/* do stuff */

	status_t retval = STATUS_ERROR;
	for (int i = 0; i < NUM_WRITE_ATTEMPTS && retval != STATUS_OK; i++) {
		retval = canWrite(CAN_ID_APDET_STATE, APDET_STATE_DEPLOY_PAYLOAD);
	}
}

void deploy_payload(void)
{
	/* do stuff */

	status_t retval = STATUS_ERROR;
	for (int i = 0; i < NUM_WRITE_ATTEMPTS && retval != STATUS_OK; i++) {
		retval = canWrite(CAN_ID_APDET_STATE, APDET_STATE_INITIAL_DESCENT);
	}
}

void detect_main_alt(void)
{
	/* do stuff */

	status_t retval = STATUS_ERROR;
	for (int i = 0; i < NUM_WRITE_ATTEMPTS && retval != STATUS_OK; i++) {
		retval = canWrite(CAN_ID_APDET_STATE, APDET_STATE_DEPLOY_MAIN);
	}
}

void deploy_main(void)
{
	/* do stuff */

	status_t retval = STATUS_ERROR;
	for (int i = 0; i < NUM_WRITE_ATTEMPTS && retval != STATUS_OK; i++) {
		retval = canWrite(CAN_ID_APDET_STATE, APDET_STATE_FINAL_DESCENT);
	}
}

void final_descent(void)
{
	/* do stuff */

	status_t retval = STATUS_ERROR;
	for (int i = 0; i < NUM_WRITE_ATTEMPTS && retval != STATUS_OK; i++) {
		retval = canWrite(CAN_ID_APDET_STATE, APDET_STATE_LANDED);
	}
}

int main()
{
	detect_launch();
	detect_burnout();
	coasting_to_test_apogee();
	test_apogee();
	deploy_drogue();
	deploy_payload();
	detect_main_alt();
	deploy_main();
	final_descent();

	while (1) {}
	return 0;
}

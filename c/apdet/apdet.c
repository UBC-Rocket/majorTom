/*
Hardware-independent functions from apdet.h
*/
#include <apdet.h>
#include <shared/can.h>

/* transition from STANDBY to POWERED_ASCENT */
static void detect_launch(void)
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

/* transition from POWERED_ASCENT to COASTING */
/* involve time to double check / as a backup? data is not stable at this point */
static void detect_burnout(void)
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

/* transition from COASTING to TEST_APOGEE */
static void coasting_to_test_apogee(void)
/* is it necessary to have coasting and apogee testing in different states?
maybe it's so that there isn't as much computation when it's far from the apogee? */
{
	/* do stuff */

	status_t retval = STATUS_ERROR;
	for (int i = 0; i < NUM_WRITE_ATTEMPTS && retval != STATUS_OK; i++) {
		retval = canWrite(CAN_ID_APDET_STATE, APDET_STATE_TEST_APOGEE);
	}

}

/* transition from TEST_APOGEE to DEPLOY DROGUE */
static void test_apogee(void)
{
	/* do stuff */

	status_t retval = STATUS_ERROR;
	for (int i = 0; i < NUM_WRITE_ATTEMPTS && retval != STATUS_OK; i++) {
		retval = canWrite(CAN_ID_APDET_STATE, APDET_STATE_DEPLOY_DROGUE);
	}
}

/* actually deploys the drogue, then transitions from DEPLOY_DROGUE to DEPLOY_PAYLOAD */
static void deploy_drogue(void)
{
	/* do stuff */

	status_t retval = STATUS_ERROR;
	for (int i = 0; i < NUM_WRITE_ATTEMPTS && retval != STATUS_OK; i++) {
		retval = canWrite(CAN_ID_APDET_STATE, APDET_STATE_DEPLOY_PAYLOAD);
	}
}

/* actually deploys the payload, then transitions from DEPLOY_PAYLOAD to INITIAL_DESCENT */
static void deploy_payload(void)
{
	/* do stuff */

	status_t retval = STATUS_ERROR;
	for (int i = 0; i < NUM_WRITE_ATTEMPTS && retval != STATUS_OK; i++) {
		retval = canWrite(CAN_ID_APDET_STATE, APDET_STATE_INITIAL_DESCENT);
	}
}

/* transitions from INITIAL_DESCENT to DEPLOY_MAIN */
static void detect_main_alt(void)
{
	/* do stuff */

	status_t retval = STATUS_ERROR;
	for (int i = 0; i < NUM_WRITE_ATTEMPTS && retval != STATUS_OK; i++) {
		retval = canWrite(CAN_ID_APDET_STATE, APDET_STATE_DEPLOY_MAIN);
	}
}

/* actually deploys the main parachute, then transitions from DEPLOY_MAIN to FINAL_DESCENT */
static void deploy_main(void)
{
	/* do stuff */

	status_t retval = STATUS_ERROR;
	for (int i = 0; i < NUM_WRITE_ATTEMPTS && retval != STATUS_OK; i++) {
		retval = canWrite(CAN_ID_APDET_STATE, APDET_STATE_FINAL_DESCENT);
	}
}

/* transitions from FINAL_DESCENT to LANDED */
static void final_descent(void)
{
	/* do stuff */

	status_t retval = STATUS_ERROR;
	for (int i = 0; i < NUM_WRITE_ATTEMPTS && retval != STATUS_OK; i++) {
		retval = canWrite(CAN_ID_APDET_STATE, APDET_STATE_LANDED);
	}
}

/**
 * @brief Apogee Detection board routine - hardware-independent implementation
 * @return Status.
 */
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
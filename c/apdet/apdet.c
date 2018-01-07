/*
Hardware-independent functions from apdet.h
*/
#include <apdet.h>
#include <shared/can.h>
#include <shared/utils.h>

/* STATIC HELPER FUNCTIONS / DRIVERS ===================================================================== */

/*
@brief Drogue deployment driver.
@return status_t
*/
extern status_t deploy_drogue()
{
	/* TODO */
	return STATUS_OK;
}

/*
@brief Payload deployment driver.
@return status_t
*/
extern status_t deploy_payload()
{
	/* TODO */
	return STATUS_OK;
}

/*
@brief Main deployment driver.
@return status_t
*/
extern status_t deploy_main()
{
	/* TODO */
	return STATUS_OK;
}


/* ROCKET FLIGHT STATE FUNCTIONS ================================================================= */

/*
@brief Transitions from STANDBY to POWERED_ASCENT after seeing NUM_CHECKS positive accelerations in a row.
@return status_t
*/
static status_t detect_launch(void)
{
	/* expect giant spike in acceleration */
	int launch_count = 0;
	float accel = 0;
	
	while (launch_count < NUM_CHECKS) { 

		can_id_t can_id;
		float can_msg;
		status_t retval = canRead(&can_id, (uint64_t *) &can_msg);
		if (retval != STATUS_OK || can_id != CAN_ID_SENSOR_ACCEL_Z) {
			continue;
		}

		accel = can_msg;

		if (accel >= SIM_LAUNCH_ACCEL) {
			launch_count++;
		} else {
			launch_count = 0;
		}
	}

	status_t retval = STATUS_ERROR;
	for (int i = 0; i < NUM_WRITE_ATTEMPTS && retval != STATUS_OK; i++) {
		retval = canWrite(CAN_ID_APDET_STATE, APDET_STATE_POWERED_ASCENT);
	}
	return STATUS_OK;
}

/*
@brief Transitions from POWERED_ASCENT to COASTING after seeing NUM_CHECKS negative accelerations in a row.
@return status_t
*/
static status_t detect_burnout(void)
{
	/* involve time to double check / as a backup? Check reasonable altitude?
	Data may not be stable at this point */
	int burnout_count = 0;
	float accel = 0;

	while (burnout_count < NUM_CHECKS) {

		can_id_t can_id;
		float can_msg;
		status_t retval = canRead(&can_id, (uint64_t *) &can_msg);
		if (retval != STATUS_OK || can_id != CAN_ID_SENSOR_ACCEL_Z) {
			continue;
		}

		accel = can_msg;

		if (accel <= 0) {
			burnout_count++;
		} else {
			burnout_count = 0;
		}
	}

	status_t retval = STATUS_ERROR;
	for (int i = 0; i < NUM_WRITE_ATTEMPTS && retval != STATUS_OK; i++) {
		retval = canWrite(CAN_ID_APDET_STATE, APDET_STATE_COASTING);
	}
	return STATUS_OK;
}

/*
@brief Transition from COASTING to DEPLOY DROGUE by checking altitude delta is negative.
@return status_t
*/
static status_t coasting_and_test_apogee(void)
{

	/* check that acceleration is 0 or positive downwards (acc >= 0 ) too? */
	int apogee_count = 0;

	float alt = 0;
	float prev_alt = 0;

	while (apogee_count < NUM_CHECKS) {

		can_id_t can_id;
		float can_msg;
		status_t retval = canRead(&can_id, (uint64_t *) &can_msg);
		if (retval != STATUS_OK || can_id != CAN_ID_SENSOR_CALC_ALTITUDE) {
			continue;
		}

		prev_alt = alt;
		alt = can_msg;

		if (alt <= prev_alt) {
			apogee_count++;
		} else {
			apogee_count = 0;
		}
	}

	status_t retval = STATUS_ERROR;
	for (int i = 0; i < NUM_WRITE_ATTEMPTS && retval != STATUS_OK; i++) {
		retval = canWrite(CAN_ID_APDET_STATE, APDET_STATE_DEPLOY_DROGUE);
	}
	return STATUS_OK;
}


/*
@brief Actually deploys the drogue, waits 3s and transitions from DEPLOY_DROGUE to DEPLOY_PAYLOAD.
@return status_t
*/
static status_t deploy_drogue_state(void)
{
	deploy_drogue();
	delay(3);

	status_t retval = STATUS_ERROR;
	for (int i = 0; i < NUM_WRITE_ATTEMPTS && retval != STATUS_OK; i++) {
		retval = canWrite(CAN_ID_APDET_STATE, APDET_STATE_DEPLOY_PAYLOAD);
	}
	return STATUS_OK;
}

/*
@brief Actually deploys the payload, then transitions from DEPLOY_PAYLOAD to INITIAL_DESCENT.
@return status_t
*/
static status_t deploy_payload_state(void)
{
	deploy_payload();

	status_t retval = STATUS_ERROR;
	for (int i = 0; i < NUM_WRITE_ATTEMPTS && retval != STATUS_OK; i++) {
		retval = canWrite(CAN_ID_APDET_STATE, APDET_STATE_INITIAL_DESCENT);
	}
	return STATUS_OK;
}

/*
@brief transitions from INITIAL_DESCENT to DEPLOY_MAIN after rocket's alt <= 3000 ft.
@return status_t
*/
static status_t detect_main_alt(void)
{
	int main_count = 0;
	float alt = 0;

	while (main_count < NUM_CHECKS) {

		can_id_t can_id;
		float can_msg;
		status_t retval = canRead(&can_id, (uint64_t *) &can_msg);
		if (retval != STATUS_OK || can_id != CAN_ID_SENSOR_CALC_ALTITUDE) {
			continue;
		}

		alt = can_msg;

		if (alt <= 3000) {
			main_count++;
		} else {
			main_count = 0;
		}
	}

	status_t retval = STATUS_ERROR;
	for (int i = 0; i < NUM_WRITE_ATTEMPTS && retval != STATUS_OK; i++) {
		retval = canWrite(CAN_ID_APDET_STATE, APDET_STATE_DEPLOY_MAIN);
	}
	return STATUS_OK;
}

/*
@brief Actually deploys the main parachute, then transitions from DEPLOY_MAIN to FINAL_DESCENT.
@return status_t
*/
static status_t deploy_main_state(void)
{
	deploy_main();

	status_t retval = STATUS_ERROR;
	for (int i = 0; i < NUM_WRITE_ATTEMPTS && retval != STATUS_OK; i++) {
		retval = canWrite(CAN_ID_APDET_STATE, APDET_STATE_FINAL_DESCENT);
	}
	return STATUS_OK;
}

/*
@brief Actually deploys the main parachute, then transitions from transitions from FINAL_DESCENT to LANDED.
@return status_t
*/
static status_t final_descent(void)
{
	int land_count = 0;

	float alt = 0;
	float prev_alt = 0;

	while (land_count < NUM_CHECKS) {

		can_id_t can_id;
		float can_msg;
		status_t retval = canRead(&can_id, (uint64_t *) &can_msg);
		if (retval != STATUS_OK || can_id != CAN_ID_SENSOR_CALC_ALTITUDE) {
			continue;
		}

		prev_alt = alt;
		alt = can_msg;

		if (alt == prev_alt) { /* give error bound? */
			land_count++;
		} else {
			land_count = 0;
		}
	}

	status_t retval = STATUS_ERROR;
	for (int i = 0; i < NUM_WRITE_ATTEMPTS && retval != STATUS_OK; i++) {
		retval = canWrite(CAN_ID_APDET_STATE, APDET_STATE_LANDED);
	}
	return STATUS_OK;
}


/* MAIN =============================================================================== */

/**
 * @brief Apogee Detection board routine - hardware-independent implementation.
 * @return Status.
 */
int main()
{
	status_t retval = canInit();
	if (retval != STATUS_OK) {
		return retval;
	}

	detect_launch();
	detect_burnout();
	coasting_and_test_apogee();
	deploy_drogue_state();
	deploy_payload_state();
	detect_main_alt();
	deploy_main_state();
	final_descent();

	while (1) {}
	return 0;
}
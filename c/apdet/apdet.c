/*
Hardware-independent functions from apdet.h
*/
#include <apdet.h>
#include <shared/can.h>
#include <shared/utils.h>

/* STATIC HELPER FUNCTIONS ===================================================================== */

static status_t calculate_altitude(float *altitude, float temperature, float pressure)
{
	*altitude = temperature + pressure; /* stub-ish, TODO */
	return STATUS_OK;
}

extern status_t deploy_drogue()
{
	return STATUS_OK;
}

extern status_t deploy_payload()
{
	return STATUS_OK;
}

extern status_t deploy_main()
{
	return STATUS_OK;
}


/* ROCKET FLIGHT STATE FUNCTIONS ===================================================================== */

/* transition from STANDBY to POWERED_ASCENT */
static status_t detect_launch(void)
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
	return STATUS_OK;
}

/* transition from POWERED_ASCENT to COASTING */
/* involve time to double check / as a backup? data is not stable at this point */
static status_t detect_burnout(void)
{
	/* giant drop in acceleration,
	return when we've seen 5 negative accelerations in a row
	then transitions to coasting state */
	int burnout_count = 0;
	float accel = 0;

	while (burnout_count < NUM_CHECKS) {

		can_id_t can_id;
		float can_msg;
		status_t retval = canRead(&can_id, (uint64_t *) &can_msg); /* read from CAN */
		if (retval != STATUS_OK || can_id != CAN_ID_SENSOR_ACCEL_Z) {
			continue;
		}

		accel = can_msg;

		if (accel <= 0) { /* if acceleration is negative. TODO: check reasonable altitude? */
			burnout_count++;
		} else {
			burnout_count = 0; /* ensures "in a row" */
		}
	}

	status_t retval = STATUS_ERROR;
	for (int i = 0; i < NUM_WRITE_ATTEMPTS && retval != STATUS_OK; i++) {
		retval = canWrite(CAN_ID_APDET_STATE, APDET_STATE_COASTING);
	}
	return STATUS_OK;
}

/* transition from COASTING to DEPLOY DROGUE */
static status_t coasting_and_test_apogee(void)
{
	/* do stuff */
	int apogee_count = 0;

	float temperature = -1;
	float pressure = -1;

	float alt = 0;
	float prev_alt = 0;

	/* wait until acceleration is 0 or positive downwards (acc >= 0 ) and the the change in altitude is negative */

	/*
	assume we'll get a sensor read for pressre and temperature in close proximity. we don't want
	to get the pressure and then 5 seconds later get the temperature and calculate alt from there because
	it won't be accurate.
	TODO: fix this by moving calculation to sensors board and reading altitude here from the bus (CAN_ID_SENSOR_CALC_ALTITUDE)
	*/
	while (apogee_count < NUM_CHECKS) {

		can_id_t can_id;
		float can_msg;
		status_t retval = canRead(&can_id, (uint64_t *) &can_msg); /* read from CAN */
		if (retval == STATUS_OK) {
			if (can_id == CAN_ID_SENSOR_TEMPERATURE) {
				temperature = can_msg;
			} else if (can_id != CAN_ID_SENSOR_PRESSURE) {
				pressure = can_msg;
			} else {
				continue;
			}
		} else {
			continue;
		}

		prev_alt = alt;

		/* TODO: Use proper float comparison */
		if (temperature != -1 && pressure != -1) {
			/* TODO: Get alt */
			calculate_altitude(&alt, temperature, pressure);
			temperature = -1;
			pressure = -1;
		} else {
			continue;
		}

		if (alt <= prev_alt) { /* if altitude delta is negative */
			apogee_count++;
		} else {
			apogee_count = 0; /* ensures "in a row" */
		}
	}


	status_t retval = STATUS_ERROR;
	for (int i = 0; i < NUM_WRITE_ATTEMPTS && retval != STATUS_OK; i++) {
		retval = canWrite(CAN_ID_APDET_STATE, APDET_STATE_DEPLOY_DROGUE);
	}
	return STATUS_OK;
}

/* actually deploys the drogue, then transitions from DEPLOY_DROGUE to DEPLOY_PAYLOAD */
static status_t deploy_drogue_state(void)
{
	deploy_drogue();

	/* wait 3 seconds until we transition to deploy_payload */
	delay(3);

	status_t retval = STATUS_ERROR;
	for (int i = 0; i < NUM_WRITE_ATTEMPTS && retval != STATUS_OK; i++) {
		retval = canWrite(CAN_ID_APDET_STATE, APDET_STATE_DEPLOY_PAYLOAD);
	}
	return STATUS_OK;
}

/* actually deploys the payload, then transitions from DEPLOY_PAYLOAD to INITIAL_DESCENT */
static status_t deploy_payload_state(void)
{
	deploy_payload();
	/* transition immediately */

	status_t retval = STATUS_ERROR;
	for (int i = 0; i < NUM_WRITE_ATTEMPTS && retval != STATUS_OK; i++) {
		retval = canWrite(CAN_ID_APDET_STATE, APDET_STATE_INITIAL_DESCENT);
	}
	return STATUS_OK;
}

/* transitions from INITIAL_DESCENT to DEPLOY_MAIN */
static status_t detect_main_alt(void)
{
	/* test if you're below 3000 ft (no accel) (main can't be deployed above that), and then transition */
	int main_count = 0;
	float alt = 0;

	while (main_count < NUM_CHECKS) {

		can_id_t can_id;
		float can_msg;
		status_t retval = canRead(&can_id, (uint64_t *) &can_msg); /* read from CAN */
		if (retval != STATUS_OK || can_id != CAN_ID_SENSOR_CALC_ALTITUDE) {
			continue;
		}

		/* TODO: calculate altitude separately  */

		if (alt <= 3000) { /* if altitude is below 3000 feet */
			main_count++;
		} else {
			main_count = 0; /* ensures "in a row" */
		}
	}


	status_t retval = STATUS_ERROR;
	for (int i = 0; i < NUM_WRITE_ATTEMPTS && retval != STATUS_OK; i++) {
		retval = canWrite(CAN_ID_APDET_STATE, APDET_STATE_DEPLOY_MAIN);
	}
	return STATUS_OK;
}

/* actually deploys the main parachute, then transitions from DEPLOY_MAIN to FINAL_DESCENT */
static status_t deploy_main_state(void)
{
	deploy_main();
	/* transition immediately */

	status_t retval = STATUS_ERROR;
	for (int i = 0; i < NUM_WRITE_ATTEMPTS && retval != STATUS_OK; i++) {
		retval = canWrite(CAN_ID_APDET_STATE, APDET_STATE_FINAL_DESCENT);
	}
	return STATUS_OK;
}

/* transitions from FINAL_DESCENT to LANDED */
static status_t final_descent(void)
{
	/* check if landed */

	status_t retval = STATUS_ERROR;
	for (int i = 0; i < NUM_WRITE_ATTEMPTS && retval != STATUS_OK; i++) {
		retval = canWrite(CAN_ID_APDET_STATE, APDET_STATE_LANDED);
	}
	return STATUS_OK;
}


/* ======= MAIN ========= */

/**
 * @brief Apogee Detection board routine - hardware-independent implementation
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
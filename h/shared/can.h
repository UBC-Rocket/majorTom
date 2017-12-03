/*
Header file for CAN bus library
*/

#ifndef CAN_H
#define CAN_H

#include <stdint.h>

#include <general.h>

/* CAN identifiers */
typedef enum can_id_enum {
	CAN_ALWAYS_PROCESS	= 11111111111,
	CAN_ALWAYS_IGNORE	= 00000000000,

	CAN_ID_APDET_STATE,

	/* IDs for data points from general IMU sensors */
	CAN_ID_SENSOR_GYRO_X,
	CAN_ID_SENSOR_GYRO_Y,
	CAN_ID_SENSOR_GYRO_Z,

	CAN_ID_SENSOR_ACCEL_X,
	CAN_ID_SENSOR_ACCEL_Y,
	CAN_ID_SENSOR_ACCEL_Z,

	CAN_ID_SENSOR_MAGNA_X,
	CAN_ID_SENSOR_MAGNA_Y,
	CAN_ID_SENSOR_MAGNA_Z,

	/* IDs for data points from barometric sensors */
	CAN_ID_SENSOR_TEMP,
	CAN_ID_SENSOR_PRESSURE,


} can_id_t;

/* Hardware-dependent functions */
extern status_t canInit(void);
extern status_t canWrite(can_id_t id, uint64_t msg);
extern status_t canRead(can_id_t *id, uint64_t *msg);

/* Hardware-independent functions */

#endif

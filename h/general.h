/*
Header file containing general macros
*/

#ifndef GENERAL_H
#define GENERAL_H

/* Return codes */
typedef enum status_enum {
	STATUS_OK        =  0,
	STATUS_ERROR     = -1,
	STATUS_BAD_PARAM = -2,
	STATUS_CAN_FILTERED	= -3
} status_t;

/* CAN identifiers */
typedef enum can_id_enum {
	CAN_ALWAYS_PROCESS	= 11111111111,
	CAN_ALWAYS_IGNORE	= 00000000000
} can_id_t;

#endif

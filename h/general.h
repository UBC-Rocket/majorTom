/*
Header file containing general macros
*/

#ifndef GENERAL_H
#define GENERAL_H

/* Return codes */
typedef enum status_enum {
	STATUS_OK        		=  0,
	STATUS_ERROR     		= -1,
	STATUS_BAD_PARAM 		= -2,
	STATUS_CAN_FILTERED		= -3,
	STATUS_CAN_WRITE_FAILED = -4,
	STATUS_CAN_READ_FAILED 	= -5
} status_t;

#endif

/*
Header file for CAN bus library
*/

#ifndef CAN_H
#define CAN_H

#include <stdint.h>
#include <stdio.h>
#include <general.h>

/* Global file pointers */
#ifdef MOCK
extern FILE *fp_can_write;
extern FILE *fp_can_read;
#endif

/* CAN identifiers */
typedef enum can_id_enum {
	CAN_ALWAYS_PROCESS	= 11111111111,
	CAN_ALWAYS_IGNORE	= 00000000000
} can_id_t;

/* CAN functions */
status_t canWrite(can_id_t id, uint64_t msg);
status_t canRead(can_id_t *id, uint64_t *msg);

#endif

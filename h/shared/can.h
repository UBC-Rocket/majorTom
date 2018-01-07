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
	CAN_ALWAYS_IGNORE	= 00000000000
} can_id_t;

/* Hardware-dependent functions */
extern status_t canInit(void);
extern status_t canWrite(can_id_t id, uint64_t msg);
extern status_t canRead(can_id_t *id, uint64_t *msg);

/* Hardware-independent functions */

#endif

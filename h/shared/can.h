/*
Header file for CAN bus library
*/

#ifndef CAN_H
#define CAN_H

#include <stdint.h>

#include <general.h>

//CAN functions go here
status_t canWrite(can_id_t id, uint64_t msg);
status_t canRead(can_id_t *id, uint64_t *msg);

#endif

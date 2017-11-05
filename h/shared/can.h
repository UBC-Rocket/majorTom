/*
Header file for CAN bus library
*/

#ifndef CAN_H
#define CAN_H

#include <general.h>

//CAN functions go here
status_t canPub();
status_t canSub();
status_t canFormat(char *formatted_msg, char *msg_to_format);
status_t canDecode();

#endif
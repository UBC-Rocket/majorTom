/*
Header file for CAN bus library
*/

#ifndef CAN_H
#define CAN_H

#include <general.h>

//CAN functions go here
status_t canPub(char *formatted_msg);
status_t canSub(char *received_msg);
status_t canFormat(char *formatted_msg, char *msg_to_format);
status_t canDecode(char *decoded_msg,  char *msg_to_decode);

#endif
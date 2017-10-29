/*
Header file for CAN bus library
*/

#ifndef CAN_H
#define CAN_H

//CAN functions go here
int canPub();
int canSub();
int canFormat(char *formatted_msg, char *msg_to_format);
int canDecode();

#endif
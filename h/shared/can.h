/*
Header file for CAN bus library
*/

#ifndef CAN_H
#define CAN_H

//CAN functions go here
int canPub(char *formatted_msg);
int canSub(char *received_msg);
int canFormat(char *formatted_msg, char *msg_to_format);
int canDecode(char *decoded_msg,  char *msg_to_decode);

#endif
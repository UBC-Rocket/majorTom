/*
Header file for SD library
*/

#ifndef SD_H
#define SD_H

#include <general.h>

/* Hardware-dependent functions */
extern status_t sdInit(void);
extern status_t sdWriteDouble(double[], int);
extern status_t sdWriteString(char[]);

/* Hardware-independent functions */

#endif

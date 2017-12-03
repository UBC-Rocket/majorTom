/*
Mock implementation of Telemetry board hardware-dependent functions
*/

#include <general.h>
#include <telem.h>

#include <shared/utils.h>
#include <shared/init.h>
#include <shared/can.h>
#include <shared/sd.h>

/* No hardware-dependent functions in telem.h yet... */
//#include <stdio.h>
//#include <unistd.h>
//#include <sys/socket.h>
//#include <sys/un.h>
//#include <stdlib.h>
#include <telem.h>

char socket_path[] = "\0hidden";
int* fd;
struct sockaddr_un* addr;

// - do socket setup here
status_t telemInit()
{
	initSend(fd, addr);
}

void initSend(int* fd, struct sockaddr_un* addr)
{
	if((*fd = socket(AF_UNIX, SOCK_DGRAM, 0)) == -1)
	{
		perror("socket error");
		exit(-1);
	}

	addr->sun_family = AF_UNIX;
	if(socket_path[0] != '\0')
	{
		unlink(socket_path);
	}

	addr->sun_family = AF_UNIX;
	memcpy(addr->sun_path, socket_path, sizeof(socket_path));

	//use connect to avoid passing more params with sendto vs write
	if(connect(*fd, (struct sockaddr*) addr, sizeof(struct sockaddr_un)) == -1)
	{
		perror("connect error");
		exit(-1);
	}
}

status_t telemWrite()
{

}

status_t telem(void)
{
	return 0;
}


/*
Mock implementation of Telemetry board hardware-dependent functions
*/

#include <general.h>
#include <telem.h>

#include <shared/utils.h>
#include <shared/init.h>
#include <shared/can.h>
#include <shared/sd.h>


char socket_path[] = "\0hidden";
struct sockaddr_un addr;
int fd; //file descriptor for sending data through unix sockets to receiver

// - do socket setup here
status_t telemInit()
{
	tsprintf("telemInit called\n");
	if(initSend(&fd, &addr) != STATUS_OK)
	{
		tsprintf("Error in telemInit\n");
	}
	return STATUS_OK;
}

status_t initSend(int* fd, struct sockaddr_un* addr)
{
	printf("initSend called\n");

	if ((*fd = socket(AF_UNIX, SOCK_DGRAM, 0)) == -1) {
		perror("socket error");
		return STATUS_ERROR;
	}
	printf("created socket\n");

	addr->sun_family = AF_UNIX;
	if (socket_path[0] != '\0') {
		unlink(socket_path);
	}

	addr->sun_family = AF_UNIX;
	memcpy(addr->sun_path, socket_path, sizeof(socket_path));

	//use connect to avoid passing more params with sendto vs write
	if (connect(*fd, (struct sockaddr*) addr, sizeof(struct sockaddr_un)) == -1) {
		perror("connect error");
		return STATUS_ERROR;
	}
	printf("initSend completed\n");

	return STATUS_OK;
}


//function stub
status_t canListen(int* id, canbus_t* canbusData) {
	if (rand() % 2 == 0) //randomly return data for testing purposes
	{
		*id = 1;
		*canbusData = 10;
	} else {
		*id = 2;
		*canbusData = 20;
	}
	return STATUS_OK;
}


status_t pbSend(pb_ostream_t* stream, pb_byte_t buffer[AMessage_size]) {
	printf("\nSending %lu bytes of payload: ", stream->bytes_written);
	fwrite(buffer, stream->bytes_written, 1, stdout); // Write to stdout raw bytes(printf stops on null byte)

	ssize_t bytesSent = send(fd, buffer, stream->bytes_written, 0);
	if (bytesSent != stream->bytes_written)
//		if(sendto(fd, arr[i], sizes[i], 0, (const struct sockaddr*) &addr, sizeof(addr)) != sizes[i])
	{
		if (bytesSent > 0) {
			perror("partial write\n");
			return STATUS_ERROR;
		} else {
			perror("write error");
			return STATUS_ERROR;
		}
	}

	return STATUS_OK;
}

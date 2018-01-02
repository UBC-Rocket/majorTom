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
int fd;
struct sockaddr_un addr;

// - do socket setup here
status_t telemInit()
{
	printf("telemInit called\n");
	initSend(&fd, &addr);
}

void initSend(int* fd, struct sockaddr_un* addr)
{
	printf("initSend called\n");

	if ((*fd = socket(AF_UNIX, SOCK_DGRAM, 0)) == -1) {
		perror("socket error");
		exit(-1);
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
		exit(-1);
	}
	printf("initSend completed\n");
}

status_t telemWrite()
{

}

status_t telem(void)
{
	return 0;
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

//listens on the bus and updates telemDataBuffer with stuff from CAN bus until timeout
//or received data from SENSOR_COUNT unique sensors
//returns STATUS_OK if we receive data
#define BAD_FLAG 0
status_t listenOnBus(AMessage* telemDataBuffer) {
	bzero(telemDataBuffer, sizeof(AMessage_size));
	int uniqueSourceCount = 0;
	for (int i = 0; i < LISTEN_QUANTUM && uniqueSourceCount < SENSOR_COUNT; i++) {
		int senderID;
		canbus_t sensorReading;
		canListen(&senderID, &sensorReading);

		//TODO: check if sensors ever return null (or else uniqueSourceCount is useless)
		if (telemDataBuffer->data[senderID] == BAD_FLAG) {
			uniqueSourceCount++;
		}
		telemDataBuffer->data[senderID] = sensorReading;
	}

	if (uniqueSourceCount > 0) {
		time_t time; getTimeSec(&time);
		telemDataBuffer->timestamp = time;
		telemDataBuffer->data_count = uniqueSourceCount;
		return STATUS_OK;
	}

	return STATUS_NO_DATA;
}





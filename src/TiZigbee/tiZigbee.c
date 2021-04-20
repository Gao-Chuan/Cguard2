#include <stdio.h>
#include <wiringPi.h>
#include <wiringSerial.h>

#include "common.h"

//char *channel = "Zigbee";

void runZigbee(void){
    // exit if this channel is not avaliable
    if (checkChannel("Zigbee") == 0){
        printf("Channel closed. \n");
        return;
    }

	int fd;
	if (wiringPiSetup() < 0)
		return;
	if ((fd = serialOpen("/dev/ttyS0", 115200)) < 0)
		return;
	serialPrintf(fd, "1");
	serialClose(fd);

	return;
}

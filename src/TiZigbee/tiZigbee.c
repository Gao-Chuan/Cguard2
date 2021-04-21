#include <stdio.h>
#include <wiringPi.h>
#include <wiringSerial.h>

#include "common.h"
#include "VendorFunction.h"

//bool gLightBulbState = false;
//pthread_mutex_t gMutexLightBulb;


void runZigbee(void){
    // exit if this channel is not avaliable
	if (checkChannel("Zigbee") == 0){
		printf("Channel closed. \n");
		return;
	}

	int fd;
	int receiveVal;  
	int end = 0;
	if (wiringPiSetup() < 0)
		return;
	if ((fd = serialOpen("/dev/ttyS0", 115200)) < 0)
		return;
	serialPrintf(fd, "1");
	
	
	
	printf("waiting... \n");
	while(end==0)
	{  

	  if(serialDataAvail(fd) > 0)
	  {      
		receiveVal=  serialGetchar(fd);
		//printf("receiveVal: %d\n", receiveVal);	
	
		switch(receiveVal)
		{
			case 235:   //on-n
			  printf("received command:>>n---turn on the light");	
			  OperateDevice(true);
			  break;
			case 233:   //off-f
			  printf("received command:>>f---turn off the light");
			  OperateDevice(false);
			  break;
			case 236:  //query-q
			  printf("received command:>>q---check the staus of light");
			  ReadDeviceStatus();
			  break;
	        case 232:  //query-e
			  printf("received command:>>e---stop Zigbee Control\n");
			  disableChannel("Zigbee");
			  end =1;
			  serialPrintf(fd, "0");
			  serialClose(fd);
			  break;
			
			//default:
			//  printf("[Error:] Unsupported command.\n");
			//  break;
		}
				
	  }
	}
	return;
}




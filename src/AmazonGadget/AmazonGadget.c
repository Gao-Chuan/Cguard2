#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "common.h"
//#include <Python.h>

void runGadget(void){

	char setup_cmd[85];
	char choose[20];
	char wake_pair_cmd[85];
	char wake_clear_cmd[85];
	
	strcpy(setup_cmd,"sudo python3 ../../lib/Alexa-Gadgets-Raspberry-Pi-Samples/launch.py --setup");
	strcpy(wake_pair_cmd,"sudo python3 ../../lib/Alexa-Gadgets-Raspberry-Pi-Samples/GadgetLed.py --pair");
	strcpy(wake_clear_cmd,"sudo python3 ../../lib/Alexa-Gadgets-Raspberry-Pi-Samples/GadgetLed.py --clear");
	//setup 
	system(setup_cmd);
	printf("setup ok\n");
	printf("pair or clear or end:\n");
	scanf("%s",(char *)&choose);

	
while(strcmp(choose,"end")!=0){
	// exit if this channel is not avaliable
    if (checkChannel("Gadget") == 0){
        printf("Gadget Channel closed. \n");
        return;
    }	

	//pair mode
	if(strcmp(choose,"pair")==0){
		system(wake_pair_cmd);
		printf("pair ok\n");
		printf("pair or clear or end:\n");
		scanf("%s",(char *)&choose);
		continue;
	}
	
	//clear mode
	else if(strcmp(choose,"clear")==0){
		system(wake_clear_cmd);
		printf("clear ok\n");
		printf("pair or clear or end:\n");
		scanf("%s",(char *)&choose);
		continue;
	}
	else{
		printf("wrong input.pair or clear or end:\n");
		scanf("%s",(char *)&choose);
		}
}
	return ;
} 

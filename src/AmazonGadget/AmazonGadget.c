#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "common.h"
//#include <Python.h>
#include <pthread.h>
#include "VendorFunction.h"

//cmd
char setup_cmd[85] = "sudo python3 ../../lib/Alexa-Gadgets-Raspberry-Pi-Samples/launch.py --setup";
char choose[20];
char wake_pair_cmd[85] = "sudo python3 ../../src/AmazonGadget/GadgetLed.py --pair";
char wake_clear_cmd[85] = "sudo python3 ../../src/AmazonGadget/GadgetLed.py --clear";


void runGadget(void){

	//setup 
	system(setup_cmd);
	printf("setup ok\n");
	//printf("pair or clear or end(p c e):\n");
	//scanf("%s",(char *)&choose);

	
while(strcmp(choose,"e")!=0){
	// exit if this channel is not avaliable
    if (checkChannel("Gadget") == 0){
        printf("Gadget Channel closed. \n");
        system(wake_clear_cmd);
		printf("\nclear ok\n");
        return;
    }
	else{
		printf("pair or clear or end(p c e):\n");
		scanf("%s",(char *)&choose);
	}	
	
	//pair mode
	if(strcmp(choose,"p")==0){

        system(wake_pair_cmd);
		printf("\npair ok\n");
		//printf("pair or clear or end(p c e):\n");
		//scanf("%s",(char *)&choose);
		//continue;
	}
	
	//clear mode
	else if(strcmp(choose,"c")==0){
		system(wake_clear_cmd);
		printf("\nclear ok\n");
		//printf("pair or clear or end(p c e):\n");
		//scanf("%s",(char *)&choose);
		//continue;
	}
	else{
		printf("wrong input.pair or clear or end(p c e):\n");
		//scanf("%s",(char *)&choose);
		//continue;
		}

}
	return ;
} 


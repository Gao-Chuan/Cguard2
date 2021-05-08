#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h> 
#include "common.h"
//#include <Python.h>
#include <pthread.h>
#include <unistd.h>
#include "VendorFunction.h"

//cmd
char setup_cmd[85] = "sudo python3 ../../lib/Alexa-Gadgets-Raspberry-Pi-Samples/launch.py --setup";
char choose[20];
char wake_pair_cmd[85] = "sudo python3 ../../src/AmazonGadget/GadgetLed.py --pair";
char wake_clear_cmd[85] = "sudo python3 ../../src/AmazonGadget/GadgetLed.py --clear";
char input;//keyboard input

void runGadget(void){
	//cancel auto setup
	//setup 
	//system(setup_cmd);


//gadget loop
while(1){
	// exit if this channel is not avaliable
    if (checkChannel("Gadget") == 0){
        printf("Gadget Channel closed. \n");
        //system(wake_clear_cmd);
		//printf("\nclear ok\n");
        return;
    }
	printf("\n+-------------------------------------------+\n");
	printf("|             gadget running                  |\n");
    printf("|        make sure setup gadget in lib        |\n");
    printf("+---------------------------------------------+\n");
	printf("enter p to start pair,c to unpair\n");
	//scanf("%s",(char *)&choose);
	input = getchar();
	//pair mode
	if(input == 'p'){
		closeotherChannel("Gadget");//close other channels
        system(wake_pair_cmd);
		printf("\ngadget pair ok\n");	
		//closeotherChannel("Gadget");//close other channels
	}
	
	//clear mode
	else if(input == 'c'){
		system(wake_clear_cmd);
		printf("\ngadget unpair and clear ok\n");
		break;//quit gadget loop
	}
	else{
		printf("Gagdet wrong input.enter p to start pair,c to unpair\n");
		}
}
	return;
} 


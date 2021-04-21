#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

#include "common.h"
//#include "amazonMQTT.h"

// First run flag
int FIRST_RUN = 1;

// To determine the accessibility status of each channel
struct type_channel_list *CHANNEL_LIST = NULL;
// The length of the channel list should be defined by the developer. 
int CHANNEL_LIST_LENGTH = 0;

// Initiate the channel list. First argument is the channels' names. Second argument
// is the length of the channel list (How many channels should be enabled).
// Initially, every channel is enabled.
// Return -1 if error occurs. Otherwise return 0.
int initChannelList(char **channel_names, size_t channel_num){
    CHANNEL_LIST_LENGTH = channel_num;
    FIRST_RUN = 1;

    CHANNEL_LIST = (struct type_channel_list *)malloc(CHANNEL_LIST_LENGTH * sizeof(struct type_channel_list));
    if (CHANNEL_LIST == NULL){
        return -1;
    }
    
    for (int i = 0; i < CHANNEL_LIST_LENGTH; i++){
        int length = strlen(channel_names[i]);
        // setup channels' names
        CHANNEL_LIST[i].channel_name = malloc(length + 1);
        if (CHANNEL_LIST[i].channel_name == NULL){
            return -1;
        }
        strncpy(CHANNEL_LIST[i].channel_name, channel_names[i], length);
        // set initial status to True.
        CHANNEL_LIST[i].enabled = 1;
        CHANNEL_LIST[i].channel_thread = 0;
    }
    
    return 0;
}

// Check the channel's availability. Return 1 if the channel is avaliable. Otherwise return 0.
// If there's no such channel or the status is broken(not 1 or 0), return -1.
int checkChannel(char *channel_name){
    for (size_t i = 0; i < CHANNEL_LIST_LENGTH; i++){
        printf("-%s-%s-", CHANNEL_LIST[i].channel_name, channel_name);
        if(strncmp(CHANNEL_LIST[i].channel_name, channel_name, strlen(channel_name)) == 0){
            if(CHANNEL_LIST[i].enabled == 1){
                // return 1 if this channel is avaliable.
                return 1;
            } else if (CHANNEL_LIST[i].enabled == 0){
                // return 0 if this channel is not avaliable.
                return 0;
            } else{
                // raise an error.
                return -1;
            }
        }
    }
    return -1;
}

// Enable a channel. This function will only change the status of CHANNEL_LIST.
// Return -1 if there's no such channel name. Otherwise return 0.
int enableChannel(char *channel_name){
    for (size_t i = 0; i < CHANNEL_LIST_LENGTH; i++){
        if(strncmp(CHANNEL_LIST[i].channel_name, channel_name, strlen(channel_name)) == 0){
            // check if this channel is running
            if (CHANNEL_LIST[i].enabled = 1 && CHANNEL_LIST[i].channel_thread != 0){
                printf("This channel is already enabled and running.\n");
                return 0;
            }
            
            // set the channel status to True.
            CHANNEL_LIST[i].enabled = 1;

            // start the channel's process.
            pthread_t *channel_thread_id = (pthread_t *)malloc(sizeof(pthread_t));
            int ThreadSuccess = 0;

            // if--- elase if---
            // compare the channel's name with every known channel's name. To launch the channel process.
            if(strcmp(channel_name, "amazon_MQTT") == 0){
                ThreadSuccess = pthread_create(channel_thread_id, NULL, (void *)runAmazonMQTT, NULL); 
                if(0 != ThreadSuccess){
                    printf("Create AWS pthread error\n");
                    exit(1);
                }
                CHANNEL_LIST[i].channel_thread = *channel_thread_id;
            }
            
             // if channel_name is Gadget call runGadget to start Gadget control
            if(strcmp(channel_name, "Gadget") == 0){
                ThreadSuccess = pthread_create(channel_thread_id, NULL, (void *)runGadget, NULL); 
                if(0 != ThreadSuccess){
                    printf("Create Gadget pthread error\n");
                    exit(1);
                }
                CHANNEL_LIST[i].channel_thread = *channel_thread_id;
            }
            
            // If this is the first running, close other channels.
            if(FIRST_RUN == 1){
                printf("First running detected.\n");
                FIRST_RUN = 0;
                for(int i = 0; i < CHANNEL_LIST_LENGTH; i++){
                    if(strncmp(CHANNEL_LIST[i].channel_name, channel_name, strlen(channel_name)) != 0){
                        CHANNEL_LIST[i].enabled = 0;
                    }
                }
                printf("All other channels have been closed.\n");
            }

            return 0;
        }
    }
    return -1;
}

// Disable a channel. This function will only change the status of CHANNEL_LIST.
// Return -1 if there's no such channel name. Otherwise return 0.
int disableChannel(char *channel_name){
        for (size_t i = 0; i < CHANNEL_LIST_LENGTH; i++){
        if(strncmp(CHANNEL_LIST[i].channel_name, channel_name, strlen(channel_name)) == 0){
            // set the channel status to False.
            CHANNEL_LIST[i].enabled = 0;
            return 0;
        }
    }
    return -1;
}

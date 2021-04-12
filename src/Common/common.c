#include <string.h>
#include <stdlib.h>

#include "common.h"

// Initiate the channel list. First argument is the channels' names. Second argument
// is the length of the channel list (How many channels should be enabled).
// Initially, every channel is disabled.
// Return -1 if malloc returns NULL. Otherwise return 0.
int initChannelList(char **channel_names, size_t channel_num){
    CHANNEL_LIST_LENGTH = channel_num;

    CHANNEL_LIST = (struct type_channel_list *)malloc(channel_num * sizeof(struct type_channel_list));
    if (CHANNEL_LIST == NULL){
        return -1;
    }
    
    for (int i = 0; i < channel_num; i++){
        int length = strlen(channel_names[i]);
        // setup channels' names
        CHANNEL_LIST[i].channel_name = malloc(channel_num * length);
        if (CHANNEL_LIST[i].channel_name == NULL){
            return -1;
        }
        strncpy(CHANNEL_LIST[i].channel_name, channel_names[i], length);
        // set initial status to False.
        CHANNEL_LIST[i].enabled = 0;
    }
    
    return 0;
}

// Check the channel's availability. Return 1 if the channel is avaliable. Otherwise return 0.
// If there's no such channel or the status is broken(not 1 or 0), return -1.
int checkChannel(char *channel_name){
    for (size_t i = 0; i < CHANNEL_LIST_LENGTH; i++){
        if(strncmp(CHANNEL_LIST[i].channel_name, channel_name, strlen(channel_name)) == 0){
            if(CHANNEL_LIST[i].enabled == 1){
                // return 1 if this channel is avaliable.
                return 1;
            } else if (CHANNEL_LIST[i].enabled == 1){
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
            // set the channel status to True.
            CHANNEL_LIST[i].enabled = 1;
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
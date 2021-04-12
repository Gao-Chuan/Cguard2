#ifndef COMMON_H
#define COMMON_H

#include <pthread.h>
// To determine the accessibility status of each channel
struct type_channel_list{
    char *channel_name;
    pthread_t channel_thread;
    int enabled;
};
struct type_channel_list *CHANNEL_LIST = NULL;
// The length of the channel list should be defined by the developer. 
int CHANNEL_LIST_LENGTH;

// An array to store channels' threads.
int RUNNING_CHANNEL = 0;

// Initiate the channel list. First argument is the channels' names. Second argument
// is the length of the channel list (How many channels should be enabled).
// Initially, every channel is disabled.
// Return -1 if malloc returns NULL. Otherwise return 0.
int initChannelList(char **channel_names, unsigned long channel_num);

// Check the channel's availability. Return 1 if the channel is avaliable. Otherwise return 0.
// If there's no such channel or the status is broken(not 1 or 0), return -1.
int checkChannel(char *channel_name);

// Enable a channel. This function will only change the status of CHANNEL_LIST.
// Return -1 if there's no such channel name. Otherwise return 0.
int enableChannel(char *channel_name);

// Disable a channel. This function will only change the status of CHANNEL_LIST.
// Return -1 if there's no such channel name. Otherwise return 0.
int disableChannel(char *channel_name);

#endif
#include <stdbool.h>
#include <stdio.h>
#include <pthread.h>  
#include <wiringPi.h>

extern bool gLightBulbState;
extern pthread_mutex_t gMutexLightBulb;

void OperateDevice(bool value,char *channel);

bool ReadDeviceStatus(void);
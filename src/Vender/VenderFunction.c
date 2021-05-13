/*VendorFunction.c is implemented by vendor*/

#include "VendorFunction.h"
#include "common.h"
#include <wiringPi.h>
#include <sys/time.h>
int operatrtime =0;

void OperateDevice(bool value,char* channel)
{   
    struct timeval tv;
    gettimeofday(&tv,NULL);
    printf("second: %ld\n", tv.tv_sec); // 秒
    printf("second2:%ld\n",tv.tv_usec );  //毫秒


    
    operatrtime = operatrtime +1;
    printf("it is the %d time to operate device", operatrtime);
    if (operatrtime == 1)
    {
        closeotherChannel(channel);
    }
    
    //led init
    char LED = 4;// <wiringPi.h> gpio23 Eighth on the upper right
    if(wiringPiSetup() < 0){
        printf("wiringPi error\n");
    }
    pinMode (LED,OUTPUT) ;

    //mutex_lock
    pthread_mutex_lock(&gMutexLightBulb); 
    gLightBulbState = value;

    if(gLightBulbState == true){
        digitalWrite(LED, 1);
        delay(100);
    }
    if(gLightBulbState == false){
        digitalWrite(LED, 0);
        delay(100);
    }   
    //mutex_unlock
    pthread_mutex_unlock(&gMutexLightBulb);
    printf("\n****Set light status to %d ****\n", gLightBulbState);
}

bool ReadDeviceStatus(void)
{
    printf("\n****Light status is %d ****\n", gLightBulbState);
    return gLightBulbState;
}

/* <wiringPi.h> control led example  */
// #include <wiringPi.h>
// char LED = 15; 
 
// int main(void)
// {
//     if(wiringPiSetup() < 0)return 1;
//     pinMode (LED,OUTPUT) ;
 
//     while(1)
//     {   
//         digitalWrite(LED, 1) ;
//         delay (200);
//         digitalWrite(LED, 0) ;
//         delay (200);
//     }   
// }

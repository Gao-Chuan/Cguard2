#include <stdio.h>
#include <pthread.h>  
#include <stdlib.h>

#include "aws_iot_log.h"

#include "common.h"
#include "amazonMQTT.h"
#include "VendorFunction.h"

bool gLightBulbState = false;
pthread_mutex_t gMutexLightBulb;

void log(char *l){
    printf("%s\n", l);
}

void iot_subscribe_callback_handler(AWS_IoT_Client *pClient, char *topicName, uint16_t topicNameLen,
									IoT_Publish_Message_Params *params, void *pData) {
    log("Amazon MQTT channel is actually running!\n");
    char cmd = 0;

    cmd = ((char*) params->payload)[0];

    switch(cmd) {
        case 'n':
			OperateDevice(true);
            break;
        case 'f':
			OperateDevice(false);
            break;
        case 'q':
            pthread_mutex_lock(&gMutexLightBulb);
			ReadDeviceStatus();
            pthread_mutex_unlock(&gMutexLightBulb);
            break;
        case 'e':
            IOT_INFO("Exiting from AWSChannel.");
            pthread_exit(NULL);
            break;
        default:
            printf("[Error:] Unsupported command.\n");
            break;
		}
}

char *cert_dir = "./cert";

void check_err(int err, int good, char* err_log){
    if(err != good){
        printf("%s\n", err_log);
        exit(1);
    }
    return;
}

int main(void){
    char *channel_names[] = {"amazon_MQTT"};
    int err;
	pthread_mutex_init(&gMutexLightBulb, NULL);

    err = initChannelList(channel_names, 1);
    check_err(err, 0, "Failed to initialize.");
    log("channel initialized!");

    certDirectory = "./cert";
    pTopicName = "myLightBulb";
    QoS qos = QOS0;
    pApplicationHandler = &iot_subscribe_callback_handler;
    pApplicationHandlerData = NULL;

    err = enableChannel("amazon_MQTT");
    check_err(err, 0, "Failed to enable channel.");
    log("channel enabled!");

    if(CHANNEL_LIST[0].channel_thread == 0){
        printf("Process error.\n");
        exit(1);
    } else{
        pthread_join(CHANNEL_LIST[0].channel_thread, NULL);
    }

    printf("End of main process.\n");

    return 0;
}
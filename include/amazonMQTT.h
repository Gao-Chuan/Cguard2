#ifndef AMAZON_MQTT_H
#define AMAZON_MQTT_H

#include "aws_iot_mqtt_client.h"

void runAmazonMQTT(char *, const char *, QoS, pApplicationHandler_t, void *);

#endif
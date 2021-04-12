/**
 * @file LightBulb.c
 * @brief simple AWS Light Bulb
 *
 * This example takes the parameters from the LightBulb.h file and establishes a connection to the AWS IoT MQTT Platform.
 * It subscribes to the topic - "myLightBulb"
 *
 * If all the certs are correct, you should see the messages received by the application in a loop.
 *
 * The application takes in the certificate path, host name , port and the number of times the publish should happen.
 *
 */
#include <limits.h>

#include "aws_iot_mqtt_client.h"
#include "aws_iot_log.h"

#include "AWSConfig.h"
#include "amazonMQTT.h"
#include "common.h"

#define HOST_ADDRESS_SIZE 255
/**
 * @brief the state of light bulb, on: ture; off: false
 */

char *channel = "amazonMQTT";

void disconnectCallbackHandler(AWS_IoT_Client *pClient, void *data) {
    IOT_WARN("MQTT Disconnect");
    IoT_Error_t rc = FAILURE;

    if(NULL == pClient) {
        return;
    }

    IOT_UNUSED(data);

    if(aws_iot_is_autoreconnect_enabled(pClient)) {
        IOT_INFO("Auto Reconnect is enabled, Reconnecting attempt will start now");
    } else {
        IOT_WARN("Auto Reconnect not enabled. Starting manual reconnect...");
        rc = aws_iot_mqtt_attempt_reconnect(pClient);
        if(NETWORK_RECONNECTED == rc) {
            IOT_WARN("Manual Reconnect Successful");
        } else {
            IOT_WARN("Manual Reconnect Failed - %d", rc);
        }
    }
}

void runAmazonMQTT(char *certDirectory, const char *pTopicName, QoS qos, pApplicationHandler_t pApplicationHandler, void *pApplicationHandlerData){
    // exit if this channel is not avaliable
    if (checkChannel(channel) == 0){
        return NULL;
    }
    /**
     * @brief Set it up in AWSConfig.h
     */
    // char certDirectory[PATH_MAX + 1] = "./certs/amazonMQTT";

    /**
     * @brief Set it up in AWSConfig.h
     */
    char HostAddress[HOST_ADDRESS_SIZE] = AWS_IOT_MQTT_HOST;

    /**
     * @brief Set it up in AWSConfig.h
     */
    uint32_t port = AWS_IOT_MQTT_PORT;

    char rootCA[PATH_MAX + 1];
    char clientCRT[PATH_MAX + 1];
    char clientKey[PATH_MAX + 1];
    char CurrentWD[PATH_MAX + 1];
    char cPayload[100];

    IoT_Error_t rc = FAILURE;

    AWS_IoT_Client *client = malloc(sizeof(AWS_IoT_Client));
    IoT_Client_Init_Params mqttInitParams = iotClientInitParamsDefault;
    IoT_Client_Connect_Params connectParams = iotClientConnectParamsDefault;

    getcwd(CurrentWD, sizeof(CurrentWD));
    snprintf(rootCA, PATH_MAX + 1, "%s/%s/%s", CurrentWD, certDirectory, AWS_IOT_ROOT_CA_FILENAME);
    snprintf(clientCRT, PATH_MAX + 1, "%s/%s/%s", CurrentWD, certDirectory, AWS_IOT_CERTIFICATE_FILENAME);
    snprintf(clientKey, PATH_MAX + 1, "%s/%s/%s", CurrentWD, certDirectory, AWS_IOT_PRIVATE_KEY_FILENAME);

    mqttInitParams.enableAutoReconnect = false; // We enable this later below
    mqttInitParams.pHostURL = HostAddress;
    mqttInitParams.port = port;
    mqttInitParams.pRootCALocation = rootCA;
    mqttInitParams.pDeviceCertLocation = clientCRT;
    mqttInitParams.pDevicePrivateKeyLocation = clientKey;
    mqttInitParams.mqttCommandTimeout_ms = 20000;
    mqttInitParams.tlsHandshakeTimeout_ms = 5000;
    mqttInitParams.isSSLHostnameVerify = true;
    mqttInitParams.disconnectHandler = disconnectCallbackHandler;
    mqttInitParams.disconnectHandlerData = NULL;

    rc = aws_iot_mqtt_init(client, &mqttInitParams);
    if(SUCCESS != rc) {
        IOT_ERROR("aws_iot_mqtt_init returned error : %d ", rc);
        return NULL;
    }

    connectParams.keepAliveIntervalInSec = 600;
    connectParams.isCleanSession = true;
    connectParams.MQTTVersion = MQTT_3_1_1;
    connectParams.pClientID = AWS_IOT_MQTT_CLIENT_ID;
    connectParams.clientIDLen = (uint16_t) strlen(AWS_IOT_MQTT_CLIENT_ID);
    connectParams.isWillMsgPresent = false;

    IOT_INFO("Connecting...");
    rc = aws_iot_mqtt_connect(client, &connectParams);
    if(SUCCESS != rc) {
        IOT_ERROR("Error(%d) connecting to %s:%d", rc, mqttInitParams.pHostURL, mqttInitParams.port);
        return NULL;
    }

    /*
     * Enable Auto Reconnect functionality. Minimum and Maximum time of Exponential backoff are set in LightBulb.h
     *  #AWS_IOT_MQTT_MIN_RECONNECT_WAIT_INTERVAL
     *  #AWS_IOT_MQTT_MAX_RECONNECT_WAIT_INTERVAL
     */
    rc = aws_iot_mqtt_autoreconnect_set_status(client, true);
    if(SUCCESS != rc) {
        IOT_ERROR("Unable to set Auto Reconnect to true - %d", rc);
        return;
    }

    IOT_INFO("Subscribing to topic: %s", pTopicName);
    rc = aws_iot_mqtt_subscribe(&client, pTopicName, strlen(pTopicName), qos, pApplicationHandler, pApplicationHandlerData);
    if(SUCCESS != rc) {
        IOT_ERROR("Error subscribing : %d ", rc);
        return;
    }
    
    while(NETWORK_ATTEMPTING_RECONNECT == rc || NETWORK_RECONNECTED == rc || SUCCESS == rc) {

        if (checkChannel(channel) != 1){
            IOT_INFO("channel is closed. Exiting...");
        }

        //Max time the yield function will wait for read messages
        rc = aws_iot_mqtt_yield(&client, 100);
        
        if(NETWORK_ATTEMPTING_RECONNECT == rc) {
            // If the client is attempting to reconnect we will skip the rest of the loop.
            continue;
        }
        
        sleep(1);
    }

    // Wait for all the messages to be received
    aws_iot_mqtt_yield(&client, 100);

    if(SUCCESS != rc) {
        IOT_ERROR("An error occurred in the loop.\n");
    } else {
        IOT_INFO("LightBulb done\n");
    }

    return;
}

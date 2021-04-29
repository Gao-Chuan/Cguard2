# Cguard2

channel guard 2

## Lib

### Amazon MQTT

path: ./lib/aws-iot-device-sdk-embedded-C

git clone https://github.com/aws/aws-iot-device-sdk-embedded-C.git

git checkout tags/v3.1.5



# Amazon Gadget

path: /lib/Alexa-Gadgets-Raspberry-Pi-Samples

The original Lib : Amazon Gadget

github：https://github.com/alexa/Alexa-Gadgets-Raspberry-Pi-Samples

> I added my amazon ID,Alexa Gadget Secret and LED-control script in the uploaded lib.

> （In gadget‘s branch ，/lib includes all codes of mqtt and gadget lib）



## gadget-fix

1. add VenderFunctionPy.py

2. add VenderFunction.c/h

3. fix bugs in gadget's branch

4. move amazon ID,Alexa Gadget Secret and LED-control script to   ./test/AmazonGadget/

5. ./lib/Alexa-Gadgets-Raspberry-Pi-Samples clones from  https://github.com/alexa/Alexa-Gadgets-Raspberry-Pi-Samples。(master branch)

   First run ./Gadget may need  configure the environment of amazon gadget. (some automatic pip3 install)
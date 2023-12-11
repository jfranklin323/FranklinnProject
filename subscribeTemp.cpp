#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MQTTClient.h"
#include "AnalogIn.h"
#include "derek_LED.h"

using namespace std;

#define ADDRESS     "tcp://io.adafruit.com:1883"
#define CLIENTID    "Beagle2"
#define TOPIC       "jfranklin323/feeds/weather.jasminetemp"
#define AUTHMETHOD  "jfranklin323"
#define AUTHTOKEN   "aio_Zgjy848QIvvcE2kzGIgwHKI9Kdcs"
#define QOS         1
#define TIMEOUT     10000L
#define LED_GPIO    "/sys/class/gpio/gpio60/"
#define THRESHOLD   23


volatile MQTTClient_deliveryToken deliveredtoken;

void delivered(void *context, MQTTClient_deliveryToken dt) {
        printf("Message with token value %d delivery confirmed\n", dt);
        deliveredtoken = dt;
}

int msgarrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message) {
        int i;
        char* payloadptr;
        printf("Message arrived\n");
        printf("     topic: %s\n", topicName);
        printf("   message: ");
        payloadptr = (char*) message->payload;
         float temperature = atof(payloadptr);
        printf("The temperature is %f\n", temperature);

        LED led(0);
        if (temperature <  THRESHOLD)
        {
                led.turnOn();
                cout<<"The temperature is less than threshold "<<endl;
        }
        else{
                led.turnOff();
        }
        MQTTClient_freeMessage(&message);
        MQTTClient_free(topicName);
        return 1;
}

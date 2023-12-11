#include <iostream>
#include <sstream>
#include <fstream>
#include <string.h>
#include "MQTTClient.h"
#include "GPIO.h"

using namespace std;


//Please replace the username, feed and token with your values
#define ADDRESS    "tcp://io.adafruit.com"
#define CLIENTID   "Beagle1"
#define TOPIC      "jfranklin323/feeds/weather.pushbutton"
#define AUTHMETHOD "jfranklin323"
#define AUTHTOKEN  "aio_Zgjy848QIvvcE2kzGIgwHKI9Kdcs"
#define QOS        1
#define TIMEOUT    10000L

int main(int argc, char* argv[]){
        char str_payload[100];
        MQTTClient client;
        cout << "Starting Beagle board MQTT Adafruit Publish Example" << endl;
        MQTTClient_connectOptions opts = MQTTClient_connectOptions_initializer;
        MQTTClient_message pubmsg = MQTTClient_message_initializer;
        MQTTClient_deliveryToken token;
        MQTTClient_create(&client, ADDRESS, CLIENTID, MQTTCLIENT_PERSISTENCE_NONE, NULL);
        opts.keepAliveInterval = 20;
        opts.cleansession = 1;
        opts.username = AUTHMETHOD;
        opts.password = AUTHTOKEN;
        int rc;
        if ((rc = MQTTClient_connect(client, &opts)) != MQTTCLIENT_SUCCESS) {
           cout << "Failed to connect, return code " << rc << endl;
           return -1;
        }
GPIO pushButton(46);
           cout<<"GPIO pin:  "<<pushButton.getNumber()<<endl;
           int sta = pushButton.getValue();
           cout<<"Status:  "<<sta<<endl; //0 = OFF , 1 = ON

           sprintf(str_payload, "%i", sta);
           pubmsg.payload = str_payload;
           pubmsg.payloadlen = strlen(str_payload);
           pubmsg.qos = QOS;
           pubmsg.retained = 0;
           MQTTClient_publishMessage(client, TOPIC, &pubmsg, &token);
           cout << "Waiting for up to " << (int)(TIMEOUT/1000) <<
                   "seconds for publication of " << str_payload <<
                   " \non top " << TOPIC << " for CLientID: " << CLIENTID << endl;
           rc = MQTTClient_waitForCompletion(client, token, TIMEOUT);
             if(rc == MQTTCLIENT_SUCCESS) {
                cout << "Message with token " << (int)token << " delivered." << endl;
             }
             else {
                     cout << "Did not complete with error code: " << rc << endl;
                     // MQTTCLIENT_SUCCESS 0           MQTTCLIENT_FAILURE -1
                     // MQTTCLIENT_DISCONNECTED -3     MQTTCLIENT_MAX_MESSAGES_INFLIGHT -4
                     // MQTTCLIENT_BAD_UTF8_STRING -5  MQTTCLIENT_NULL_PARAMETER -6
                     // MQTTCLIENT_TOPICNAME_TRUNCATED -7   MQTTCLIENT_BAD_STRUCTURE -8
                     // MQTTCLIENT_BAD_QOS   -9        MQTTCLIENT_SSL_NOT_SUPPORTED   -10
            }
MQTTClient_disconnect(client, 10000);
MQTTClient_destroy(&client);
return rc;
}

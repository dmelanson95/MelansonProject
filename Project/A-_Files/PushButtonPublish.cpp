/*
Altered version of Molloy's publish.cpp file
Altered by David Melanson for IoT Final Project
Fulfills requirement 4 for B+ tier

Reads input from push button attached to P8.16 
0 = pressed
1 = not pressed

sends status of push button to Adafruit IO whenever it changes.
*/



#include <iostream>
#include <sstream>
#include <fstream>
#include <string.h>
#include "MQTTClient.h"
#include "GPIO.h"
#include <stdbool.h>
using namespace std;
using namespace exploringBB;

//Please replace the username, feed and token with your values
#define ADDRESS    "tcp://io.adafruit.com"
#define CLIENTID   "Beagle2"
#define TOPIC      "david_melanson/feeds/iot-final-project.r4"
#define AUTHMETHOD "david_melanson"
#define AUTHTOKEN  "aio_SjEI679FDe6fg7rJTxVfgbRA9GPb"
#define QOS        1
#define TIMEOUT    10000L


int main(int argc, char* argv[]) {
   int lastValue = 0;
   int currentValue = 1;
   GPIO P816(46);
   char str_payload[100];          // Set your max message size here
   char ch;
   cout << "Press <Enter> to send data, press Q to quit at any time." << endl;
   int rc;
   MQTTClient client;
   MQTTClient_connectOptions opts = MQTTClient_connectOptions_initializer;
   MQTTClient_message pubmsg = MQTTClient_message_initializer;
   MQTTClient_deliveryToken token;
   MQTTClient_create(&client, ADDRESS, CLIENTID, MQTTCLIENT_PERSISTENCE_NONE, NULL);
   opts.keepAliveInterval = 20;
   opts.cleansession = 1;
   opts.username = AUTHMETHOD;
   opts.password = AUTHTOKEN;
   if ((rc = MQTTClient_connect(client, &opts)) != MQTTCLIENT_SUCCESS) {
      cout << "Failed to connect, return code " << rc << endl;
      return -1;
   }
   while(ch != 'Q'){
      currentValue = !P816.getValue();
      if(currentValue != lastValue){
         sprintf(str_payload, "%i", currentValue);
         pubmsg.payload = str_payload;
         pubmsg.payloadlen = strlen(str_payload);
         pubmsg.qos = QOS;
         pubmsg.retained = 0;
         MQTTClient_publishMessage(client, TOPIC, &pubmsg, &token);
         cout << "Waiting for up to " << (int)(TIMEOUT/1000) <<
            " seconds for publication of " << str_payload <<
            " \non topic " << TOPIC << " for ClientID: " << CLIENTID << endl;
         rc = MQTTClient_waitForCompletion(client, token, TIMEOUT);
         if(rc == MQTTCLIENT_SUCCESS) {
         cout << "Message with token " << (int)token << " delivered." << endl;
         }
         else {
            cout << "Did not complete with error code: " << rc << endl;
            break;
         // MQTTCLIENT_SUCCESS 0           MQTTCLIENT_FAILURE -1
         // MQTTCLIENT_DISCONNECTED -3     MQTTCLIENT_MAX_MESSAGES_INFLIGHT -4
         // MQTTCLIENT_BAD_UTF8_STRING -5  MQTTCLIENT_NULL_PARAMETER -6
         // MQTTCLIENT_TOPICNAME_TRUNCATED -7   MQTTCLIENT_BAD_STRUCTURE -8
         // MQTTCLIENT_BAD_QOS   -9        MQTTCLIENT_SSL_NOT_SUPPORTED   -1
         }
         lastValue = currentValue;
         ch = getchar();
      }
      //ch = getchar();
   }
   MQTTClient_disconnect(client, 10000);
   MQTTClient_destroy(&client);
   //return rc;
}


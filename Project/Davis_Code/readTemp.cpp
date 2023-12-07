#include <iostream>
#include <sstream>
#include <fstream>
#include <string.h>
#include "MQTTClient.h"
#include "AnalogIn.h"
using namespace std;

//Please replace the username, feed and token with your values
#define ADDRESS    "tcp://io.adafruit.com"
#define CLIENTID   "Beagle1"
#define TOPIC      "davis_farrow/feeds/analog.temp"
#define AUTHMETHOD "davis_farrow"
#define AUTHTOKEN  "aio_MKxX75nvPQO2OAbP1k0CVlBqhb7P"
#define QOS        1
#define TIMEOUT    10000L

float getTemperature(int adc_value) {     // from the TMP36 datasheet
	float cur_voltage = adc_value * (1.80f/4096.0f); // Vcc = 1.8V, 12-bit
	float diff_degreesC = (cur_voltage-0.75f)/0.01f;
	return (25.0f + diff_degreesC);
}

int main(int argc, char* argv[]) {
   AnalogIn AIN0(0);
   char str_payload[100];          // Set your max message size here
   MQTTClient readTemp;
   cout << "Starting Beagle board MQTT Adafruit Publish for CPE 422 Project 1" << endl;
   MQTTClient_connectOptions opts = MQTTClient_connectOptions_initializer;
   MQTTClient_message pubmsg = MQTTClient_message_initializer;
   MQTTClient_deliveryToken token;
   MQTTClient_create(&readTemp, ADDRESS, CLIENTID, MQTTCLIENT_PERSISTENCE_NONE, NULL);
   opts.keepAliveInterval = 20;
   opts.cleansession = 1;
   opts.username = AUTHMETHOD;
   opts.password = AUTHTOKEN;
   int rc;
   if ((rc = MQTTClient_connect(readTemp, &opts)) != MQTTCLIENT_SUCCESS) {
      cout << "Failed to connect, return code " << rc << endl;
      return -1;
   }
   sprintf(str_payload, "%f", getTemperature(AIN0.readAdc()));
   pubmsg.payload = str_payload;
   pubmsg.payloadlen = strlen(str_payload);
   pubmsg.qos = QOS;
   pubmsg.retained = 0;
   MQTTClient_publishMessage(readTemp, TOPIC, &pubmsg, &token);
   cout << "Waiting for up to " << (int)(TIMEOUT/1000) <<
        " seconds for publication of " << str_payload <<
        " \non topic " << TOPIC << " for ClientID: " << CLIENTID << endl;
   rc = MQTTClient_waitForCompletion(readTemp, token, TIMEOUT);
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
   MQTTClient_disconnect(readTemp, 10000);
   MQTTClient_destroy(&readTemp);
   return rc;
}


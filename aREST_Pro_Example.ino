/*
  Re_Edit : Niwantha ... (Algobel Team)
  .......................
                          ......... Codes from (https://arest.io) i used this to explain   
                                    .........= 
                                    
  This a simple example of the aREST Library for the ESP8266 WiFi chip.
  This example illustrate the cloud part of aREST that makes the board accessible from anywhere
  See the README file for more details.

  Written in 2016 by Marco Schwartz under a GPL license.
*/

// Import required libraries
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <aREST.h>

// Clients
WiFiClient espClient;
PubSubClient client(espClient);

// Create aREST instance
aREST rest = aREST(client);

// aREST Pro key (that you can get at dashboard.arest.io)
char * key = "axxpm3yv10njwwb5"; // API Key ( please check account.png) 

// WiFi parameters
const char* ssid = "feelingHot"; // your wifi SSID 
const char* password = "nrl1633n"; // above SSID password 


// Functions
void callback(char* topic, byte* payload, unsigned int length);

void setup(void)
{
  // Start Serial
  Serial.begin(115200);

  // Set aREST key
  rest.setKey(key, client);

  // Set callback
  client.setCallback(callback);

 

// Give name to device
  rest.set_name("algobel_device");

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Set output topic
  char* out_topic = rest.get_topic();

}

void loop() {

  // Connect to the cloud
  rest.handle(client);

}

// Handles message arrived on subscribed topic(s)
void callback(char* topic, byte* payload, unsigned int length) {

  rest.handle_callback(client, topic, payload, length);

}

 
#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#define Relay1            D6
#define Relay2            D5
#define Relay3            D2
#define Relay4            D1
//#define RelayN          DN (Add extra devices if needed)


#define WLAN_SSID       "Ansara act"             // Your SSID
#define WLAN_PASS       "Ansaraact@1234"        // Your password

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME  "Find it from your adafruit account"
#define AIO_KEY       "Find it from your adafruit account"

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;
// or... use WiFiFlientSecure for SSL
//WiFiClientSecure client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

/*------------------------------------ Feeds -------------------------------------------------*/


// Setup a feed called 'on-off' for subscribing to changes.
Adafruit_MQTT_Subscribe Hall_Light = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME"/feeds/Relay1"); // FeedName
Adafruit_MQTT_Subscribe Room_Light = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Relay2");
Adafruit_MQTT_Subscribe TV = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Relay3");
Adafruit_MQTT_Subscribe AC = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Relay4");
//Adafruit_MQTT_Subscribe Light = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Relay5");
//Add as many connections as you nees

void MQTT_connect();

void setup() {
  Serial.begin(115200);

  pinMode(Relay1, OUTPUT);
  pinMode(Relay2, OUTPUT);
  pinMode(Relay3, OUTPUT);
  pinMode(Relay4, OUTPUT);
  //pinMode(RelayN, OUTPUT);
  
  
  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); 
  Serial.println(WiFi.localIP());
 

  // Setup MQTT subscription for onoff feed.
  mqtt.subscribe(&Hall_Light);
  mqtt.subscribe(&TV);
  mqtt.subscribe(&Room_Light);
  mqtt.subscribe(&AC);
  //mqtt.subscribe(&OtherDevices);
}

void loop() {
 
  MQTT_connect();
  

  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(20000))) {
    if (subscription == &Hall_Light) {
      Serial.print(F("Got: "));
      Serial.println((char *)Hall_Light.lastread);
      int Hall_Light_State = atoi((char *)Hall_Light.lastread);
      digitalWrite(Relay1, Hall_Light_State);
      
    }
    if (subscription == &Room_Light) {
      Serial.print(F("Got: "));
      Serial.println((char *)Room_Light.lastread);
      int Room_Light_State = atoi((char *)Room_Light.lastread);
      digitalWrite(Relay2, Room_Light_State);
    }
    if (subscription == &TV) {
      Serial.print(F("Got: "));
      Serial.println((char *)TV.lastread);
      int TV_State = atoi((char *)TV.lastread);
      digitalWrite(Relay3, TV_State);
    }
    if (subscription == &AC) {
      Serial.print(F("Got: "));
      Serial.println((char *)AC.lastread);
      int AC_State = atoi((char *)AC.lastread);
      digitalWrite(Relay4, AC_State);
    }
/*    if (subscription == &OtherDevices) {
      Serial.print(F("Got: "));
      Serial.println((char *)OtherDevices.lastread);
      int OtherDevices_State = atoi((char *)OtherDevices.lastread);
      digitalWrite(Relay4, OtherDevices_State);
      } */
    
  }

}

void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000);  // wait 5 seconds
    retries--;
    if (retries == 0) {
      // basically die and wait for WDT to reset me
      while (1);
    }
  }
  Serial.println("MQTT Connected!");
  
}

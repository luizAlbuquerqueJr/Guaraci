#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#define Rele1            D0
#define Rele2            D1

#define WLAN_SSID       "Luiz Albuquerque"             // Your SSID
#define WLAN_PASS       "32545748"        // Your password

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "io.adafruit.com" //Adafruit Server
#define AIO_SERVERPORT  1883                   
#define AIO_USERNAME  "luizAlbuquerqueJr"
#define AIO_KEY       "aio_zfhl779xwTqiReErEEpe3EWQa3HA"

//WIFI CLIENT
WiFiClient client;

ESP8266WebServer server(80);

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

Adafruit_MQTT_Subscribe Curtain = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/persiana");


void MQTT_connect();
String webString=""; 

void setup() {
  Serial.begin(115200);

  pinMode(Rele1, OUTPUT);
  pinMode(Rele2, OUTPUT);

  digitalWrite(Rele1, 0);
  digitalWrite(Rele2, 0);
  
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

  server.begin();
  Serial.println("Server started");

  server.on("/open", [](){  // if you add this subdirectory to your webserver call, you get text below :)
    webString="Abrindo cortina";   // Arduino has a hard time with float to string
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.send(200, "text/plain", webString);            // send to someones browser when asked
    engineAntiClockWise();
    delay(3000);
    digitalWrite(Rele1, 0);
    digitalWrite(Rele2, 0);
  });

  server.on("/close", [](){  // if you add this subdirectory to your webserver call, you get text below :)
    webString="Fechando cortina";
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.send(200, "text/plain", webString);               // send to someones browser when asked
    engineClockWise();
    delay(3000);
    digitalWrite(Rele1, 0);
    digitalWrite(Rele2, 0);
  });
 
  mqtt.subscribe(&Curtain);
}

void loop() {
 
  MQTT_connect();
  
  Adafruit_MQTT_Subscribe *subscription;
  while(1){
    server.handleClient();
    Serial.println("aaa");
     MQTT_connect();
    if ((subscription = mqtt.readSubscription(1000))) {
      Serial.println("aaa1");
      if (subscription == &Curtain) {
        Serial.print(F("Got: "));
        Serial.println(!(char *)Curtain.lastread);
        int Curtain_State = atoi((char *)Curtain.lastread);
        if( Curtain_State == 0) {
          engineClockWise();
        }else {
          engineAntiClockWise();
        }
        delay(3000);
        digitalWrite(Rele1, 0);
        digitalWrite(Rele2, 0);
      }     
    }
  }
}

void engineClockWise(){
  Serial.println("horário");
  digitalWrite(Rele1, 1);
  digitalWrite(Rele2, 0);
}

void engineAntiClockWise(){
  Serial.println("anti horário");
  digitalWrite(Rele1, 0);
  digitalWrite(Rele2, 1);
}

void MQTT_connect() {
  int8_t ret;

  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  
  while ((ret = mqtt.connect()) != 0) {
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000); 
    retries--;
    if (retries == 0) {
      while (1);
    }
  }
  Serial.println("MQTT Connected!");
}

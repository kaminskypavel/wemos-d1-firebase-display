// FirebaseDemo_ESP8266 is a sample that demo the different functions
// of the FirebaseArduino API.

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include "config.h"
  
const char* names[]=  {"James", "Michael", "Jane", "Michelle"};
int randNamesIdx = 0;

void setup() {
  Serial.begin(115200);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  pinMode(LED_BUILTIN, OUTPUT);

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  // turn on the led
  digitalWrite(LED_BUILTIN, HIGH);

  // set string value
  randNamesIdx  = rand()%sizeof(names) / sizeof(names[0]);
  Firebase.setString("message", "hello world, " + String(names[randNamesIdx]));
  
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /message failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(2000);

  // turn off the led
  digitalWrite(LED_BUILTIN, LOW);

  // get value 
  Serial.print("reading from firebase: ");
  Serial.println(Firebase.getString("message"));

  delay(2000);
}
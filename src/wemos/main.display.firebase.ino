// FirebaseDemo_ESP8266 is a sample that demo the different functions
// of the FirebaseArduino API.

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "config.h"

// --------------------------------------- OLED CONFIG ------------------------------------- //
// SCL GPIO5
// SDA GPIO4
#define OLED_RESET 0 // GPIO0
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH 16

#if (SSD1306_LCDHEIGHT != 48)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

void setup_display()
{
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // initialize with the I2C addr 0x3C (for the 64x48)
}

void display_text(String text, bool isInverse = false)
{
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  if (isInverse)
  {
    display.setTextColor(BLACK, WHITE);
  }
  display.println(text);
  // display.setTextSize(2);
  // display.setTextColor(WHITE);
  display.display();
}

void display_debug(String text)
{
  display_text(text, false);
}

void display_circle()
{
  display.clearDisplay();
  for (int16_t i = 0; i < display.height(); i += 2)
  {
    display.drawCircle(display.width() / 2, display.height() / 2, i, WHITE);
    display.display();
    delay(0.5);
  }
}
// --------------------------------------- Firebase ------------------------------------- //
void setup_firebase()
{
  display_debug("Firebase");
  delay(1000);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  display_debug("Connected!");
  delay(1000);
}
// --------------------------------------- Wifi ------------------------------------- //
void setup_wifi()
{
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  display_debug("Wifi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }

  delay(1000);
  Serial.println();
  Serial.print("connected: ");
  display_debug("Connected!");
  Serial.println(WiFi.localIP());
  delay(1000);
  display_circle();
  delay(1000);
}

// --------------------------------------- Main ------------------------------------- //
String oldFbValue = "";

void setup()
{
  Serial.begin(115200);

  setup_display();
  setup_wifi();
  setup_firebase();
  //pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  Serial.print("reading from firebase: ");
  String fbText = String(Firebase.getString("message"));
  Serial.println(fbText);

  if (oldFbValue.compareTo(fbText) != 0)
  {

    display_circle();
    oldFbValue = fbText;
    delay(200);
    display_text(fbText);
  }
}
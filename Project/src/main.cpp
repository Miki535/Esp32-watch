#include <Arduino.h>
#include <Wire.h>
#include <WiFi.h>
#include <time.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <ctime>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 

using namespace std;

const char* ssid = "SSID";
const char* password = "PASSWORD";

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);
  
  configTime(2 * 3600, 0, "pool.ntp.org");

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    display.clearDisplay();

    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(8, 25);
    display.println("Bad WiFi!");

    display.display();
    delay(500);
  }
}

void loop() {
  auto now = chrono::system_clock::now();

  time_t now_t = chrono::system_clock::to_time_t(now);
  tm now_tm = *localtime(&now_t);

  char buffer[32];
  strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &now_tm);

  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(10, 5);
  display.println("Date/Time");

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(5, 30);
  display.println(buffer);

  display.display(); 

  delay(1000);
}
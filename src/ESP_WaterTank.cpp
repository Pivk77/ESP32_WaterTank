/*********
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*********/

// Import required libraries
#include <Arduino.h>
#include <SPIFFS.h>
#include <Wire.h>

const int PS_DOUT_PIN = 23;
const int PS_SCK_PIN = 22;
const int BTN_PIN = 21;

String apiKey = "D9IG6H86KEPN5V8Q";
String thingspeakChannelID = "1260986";

#include "Sensor.h"

Sensor pressureSensor(PS_DOUT_PIN, PS_SCK_PIN);

#include "Global.h"

void setup()
{
  pinMode(BTN_PIN, INPUT);
  // Serial port for debugging purposes
  Serial.begin(115200);

  // Initialize SPIFFS
  if (!SPIFFS.begin())
  {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
  wifiConnect();
  initWebServer();
}

void loop()
{
  Serial.println(pressureSensor.raw());
}
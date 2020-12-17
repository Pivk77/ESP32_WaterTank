#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

AsyncWebServer server(80);

// Replace with your network credentials
const char *ssid = "TP-LINK";
const char *password = "05261105PIKOS";

String readRaw()
{
    return String(pressureSensor.raw());
}
String readHeight()
{
    return String(pressureSensor.height());
}
String readVolume()
{
    return String(pressureSensor.volume());
}

void initWebServer()
{
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/index.html");
    });
    server.on("/pressure", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send_P(200, "text/plain", readRaw().c_str());
    });
    server.on("/height", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send_P(200, "text/plain", readHeight().c_str());
    });
    server.on("/volume", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send_P(200, "text/plain", readVolume().c_str());
    });
    // Start server
    server.begin();
}

void wifiConnect()
{
    // Connect to Wi-Fi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("Connecting to WiFi..");
    }

    // Print ESP32 Local IP Address
    Serial.println(WiFi.localIP());
}

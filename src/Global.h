#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

AsyncWebServer server(80);

// Replace with your network credentials
const char *ssid = "SSID_here";
const char *password = "PASSWORD_here";

void initWebServer()
{
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/index.html");
    });
    server.on("/pressure", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send_P(200, "text/plain", String(pressureSensor.raw()).c_str());
    });
    server.on("/height", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send_P(200, "text/plain", String(pressureSensor.height()).c_str());
    });
    server.on("/volume", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send_P(200, "text/plain", String(pressureSensor.volume()).c_str());
    });
    server.on("/calibrateMin", HTTP_GET, [](AsyncWebServerRequest *request) {
        Serial.println("CalibrateMin request: ");
        request->send(200);
    });
    server.on("/calibrateMax", HTTP_GET, [](AsyncWebServerRequest *request) {
        Serial.println("CalibrateMax request: ");
        request->send(200);
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

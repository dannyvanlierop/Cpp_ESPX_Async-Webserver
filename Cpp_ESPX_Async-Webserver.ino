// Replace with your network credentials
#define WIFI_SSID        "SSID"
#define WIFI_PASSWORD    "PASSWORD"

#include <Arduino.h>
// Import required libraries
#if defined ARDUINO_ARCH_ESP32 || ESP32 || ARDUINO_ESP32_DEV
  #include <WiFi.h>
  #include <AsyncTCP.h>
#elif defined ARDUINO_ARCH_ESP8266 || ESP8266 || ARDUINO_ESP8266_WEMOS_D1MINI
  #include <ESP8266WiFi.h>
  #include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

void notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}

void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);
  
  // Connect to Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }
  Serial.print("Local IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(200, "text/plain", "Hello, world");
  });
  
  server.onNotFound(notFound);
  
  // Start server
  server.begin();

}

void loop() {

}

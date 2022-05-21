#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

const char* ssid = "No Pineapple";
const char* password = "7 Salutations";

#define STRIP_LEN 30
Adafruit_NeoPixel strip0(STRIP_LEN, 15, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip1(STRIP_LEN, 0, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2(STRIP_LEN, 16, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip3(STRIP_LEN, 5, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 50

int64_t last_active_time = 0;

int rand_rgb()
{
  return rand() / (RAND_MAX / 255);
}

void setup() {
    strip0.begin();
    strip1.begin();
    strip2.begin();
    strip3.begin();


    Serial.begin(115200);
    Serial.println("Booting");
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    uint8_t result = WiFi.waitForConnectResult();
    if (result != WL_CONNECTED)
    {
        Serial.println("WiFi Connection Failed!");
    }
    else
    {
        Serial.println("WiFi Connected.");
    }

    ArduinoOTA
    .onStart([]() {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
        type = "sketch";
      else // U_SPIFFS
        type = "filesystem";

      // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
      Serial.println("Start updating " + type);
    })
    .onEnd([]() {
      Serial.println("\nEnd");
    })
    .onProgress([](unsigned int progress, unsigned int total) {
      Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    })
    .onError([](ota_error_t error) {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR) Serial.println("End Failed");
    });

  ArduinoOTA.begin();

  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}
void loop() {
    ArduinoOTA.handle();

    if (millis() > (last_active_time + DELAYVAL))
    {
        last_active_time = millis();
        strip0.clear();
        strip1.clear();
        strip2.clear();
        strip3.clear();
        for (size_t i = 0; i < STRIP_LEN; i++)
        {
          rand();
            strip0.setPixelColor(i, strip0.Color(rand_rgb(), rand_rgb(), rand_rgb()));
            strip1.setPixelColor(i, strip1.Color(rand_rgb(), rand_rgb(), rand_rgb()));
            strip2.setPixelColor(i, strip2.Color(rand_rgb(), rand_rgb(), rand_rgb()));
            strip3.setPixelColor(i, strip3.Color(rand_rgb(), rand_rgb(), rand_rgb()));

            strip0.show();
            strip1.show();
            strip2.show();
            strip3.show();
            delay(DELAYVAL);
        }
    }
}
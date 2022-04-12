#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel strip0(10, 15, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip1(10, 0, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2(10, 16, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip3(10, 5, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 500

void setup() {
    strip0.begin();
    strip1.begin();
    strip2.begin();
    strip3.begin();
}
void loop() {
    strip0.clear();
    strip1.clear();
    strip2.clear();
    strip3.clear();
    for (size_t i = 0; i < 10; i++)
    {
        strip0.setPixelColor(i, strip0.Color(0, 150, 0));
        strip1.setPixelColor(i, strip1.Color(0, 150, 0));
        strip2.setPixelColor(i, strip2.Color(0, 150, 0));
        strip3.setPixelColor(i, strip3.Color(0, 150, 0));

        strip0.show();
        strip1.show();
        strip2.show();
        strip3.show();
        delay(DELAYVAL);
    }
}
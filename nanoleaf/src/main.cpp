#include <Arduino.h>
#include "effect.h"

void setup() {
  FastLED.addLeds<WS2812B, PINO_FITA, GRB>(fita, NUM_LEDS_FITA);
  FastLED.setBrightness(200);

  Serial.begin(115200);
}

void loop() {
  raioArcoiris();
  cometa(150);
}
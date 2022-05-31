#include <FastLED.h>
#include "paletas.h"

#define NUM_LEDS_FITA 30
#define pinData 14

CRGB fita[NUM_LEDS_FITA];

uint8_t beatA = 0;
uint8_t old_beatA = 0;
uint8_t beatB = 0;
int contador = 0;
uint8_t hue = 0;


void setup() {
  pinMode(pinData, OUTPUT);
  FastLED.addLeds<WS2812B, pinData, GRB>(fita, NUM_LEDS_FITA);
  FastLED.setBrightness(200);
  Serial.begin(115200);
  delay(100);
  Serial.println("Iniciando Fita");

  for (int i = 0; i<30; i++ ){
    fita[i] = CRGB::Red;
    FastLED.show();
  }
}
void loop() {
  Serial.println("Iniciando Fita");
}

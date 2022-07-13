#include <Arduino.h>
#include <FastLED.h>
#include "effects.h"

#define touch 2

int contador = 0;
uint8_t color = 0;

void(* resetFunc) (void) = 0;

void pinTouch (){
  delay(50);
  FastLED.show();
  fillSolidColor(CRGB::Black);
  contador++;
  Serial.println(contador);
  loop();
}

void setup() {
  pinMode(touch, INPUT);
  Serial.begin(9600);

  FastLED.addLeds<WS2812B, PINO_FITA, GRB>(fita, NUM_LEDS_FITA);
  FastLED.setBrightness(100);
  attachInterrupt(digitalPinToInterrupt(touch), pinTouch, RISING);

}

void loop() {
  delay(100);
  if (contador == 0){
    while (1)
    {
      delay(100);
      raioArcoiris();
    }
  }
  else if (contador == 1)
  {
    while (1)
    {
      delay(100);
      cometa(color, 1);
    }
  }
  else if (contador == 2)
  {
    while (1)
    {
      delay(100);
      fillSolidColor(CRGB::Black);
    }
  }
  else if (contador == 3)
  {
    resetFunc();
  }
}

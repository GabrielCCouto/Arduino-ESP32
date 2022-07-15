#include <Arduino.h>
#include <FastLED.h>
#include "effects.h"

#define touch 2

int contador = 0;

void(* resetFunc) (void) = 0;

void pinTouch (){
  delay(100);
  FastLED.show();
  fillSolidColor(CRGB::Black);
  contador++;
  Serial.println(contador);
  loop();
}

void setup() {
  pinMode(touch, INPUT);
  Serial.begin(115200);

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
      uint8_t color = 200;
      cometa(color);
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
    while (1)
    {
      delay(100);
      gradienteOndas(6);
    }
  }
  else if (contador == 4)
  {
    while (1)
    {
      delay(100);
      fillSolidColor(CRGB::White);
    }
  }
  else if (contador == 5)
  {
    while (1)
    {
      delay(100);
      fillSolidColor(CRGB::Blue);
    }
  }
  else if (contador == 6)
  {
    while (1)
    {
      delay(100);
      fillSolidColor(CRGB::DarkCyan);
    }
  }
  else if (contador == 7)
  {
    while (1)
    {
      delay(100);
      fillSolidColor(CRGB::GreenYellow);
    }
  }
  else if (contador == 8)
  {
    while (1)
    {
      delay(100);
      fillSolidColor(CRGB::Red);
    }
  }
  else if (contador == 9)
  {
    while (1)
    {
      delay(100);
      fillSolidColor(CRGB::Purple);
    }
  }
  else if (contador == 10)
  {
    resetFunc();
  }
}

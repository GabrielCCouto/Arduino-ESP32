#include <Arduino.h>
#include <FastLED.h>
#include "effects.h"

#define touch 2

int contador = 0;
int effectCount = 0;

void(* resetFunc) (void) = 0;

void pinTouch (){
  contador++;
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
  if (contador == 0){
    fillSolidColor(CRGB::Black);
  }
  else if (contador == 1){
    uint8_t color = 125;
    cometa(color);
  }
  else if (contador == 2){
    raioArcoirisCircular();
  }
  else if (contador == 3){
    effectCount++;
    gradienteOndas(effectCount);
    if (effectCount == 10)
    {
      effectCount = 0;
    }
  }
  else if (contador == 4){
    respiracao(255);
  }
  else if (contador == 5){
    gradienteMovendo();
  }
  else if (contador == 6){
    PixelsAleatorios();
  }
  else if (contador == 7){
    bolasColoridas();
  }
  else if (contador == 8){
    explosao();
  }
  else if (contador == 9){
    circular(125);
  }
    else if (contador == 10){
    raioArcoiris();
  }
  else if (contador == 11){
    fillSolidColor(CRGB::Blue);
  }
  else if (contador == 12){
    fillSolidColor(CRGB::DarkCyan);
  }
  else if (contador == 13)
  {
    resetFunc();
  }
}

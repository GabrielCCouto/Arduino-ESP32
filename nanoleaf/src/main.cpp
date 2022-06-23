#include <Arduino.h>
#include "effect.h"

// Cometa
uint8_t color = 0;
int tipo = 2;

//Respiração
byte selcor = 100;
uint8_t velocidade = 1; // Colocar 1, 2 ou 3

void setup() {
  FastLED.addLeds<WS2812B, PINO_FITA, GRB>(fita, NUM_LEDS_FITA);
  FastLED.setBrightness(200);

  Serial.begin(115200);
}

void loop() {
  //raioArcoiris();
  //cometa(color, tipo);
  //respiracao(selcor, velocidade);
  //explosao();
  //gradienteOndas();
  fullWhite();
}
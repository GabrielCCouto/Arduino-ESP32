#include <FastLED.h>
#include <EEPROM.h>
#include "effects.h"

#define touch 2

int contador;
int effectCount = 0;
int memory_adress = 0;
int effect_counter = 0;
int led_off = 0;

void(* resetFunc) (void) = 0;

void pinTouch (){
  update_effect();
  resetFunc();
}

void update_effect(){
  Serial.println("Effect Updated...");
  EEPROM.update(memory_adress, (effect_counter + 1));
}

void setup() {
  pinMode(touch, INPUT);
  Serial.begin(115200);

  EEPROM.begin();
  delay(300);
  if (digitalRead(touch) == HIGH){
    EEPROM.update(memory_adress, led_off);
    resetFunc();
  }
  effect_counter = EEPROM.read(memory_adress);
  Serial.print("Effect Value: ");
  Serial.println(effect_counter);

  FastLED.addLeds<WS2812B, PINO_FITA, GRB>(fita, NUM_LEDS_FITA);
  FastLED.setBrightness(100);
  attachInterrupt(digitalPinToInterrupt(touch), pinTouch, RISING);

}

void loop() {
  if (effect_counter == 0){
    fillSolidColor(CRGB::Black);
  }
  else if (effect_counter == 1){
    uint8_t color = 125;
    cometa(color);
  }
  else if (effect_counter == 2){
    raioArcoirisCircular();
  }
  else if (effect_counter == 3){
    effectCount++;
    gradienteOndas(effectCount);
    if (effectCount == 10)
    {
      effectCount = 0;
    }
  }
  else if (effect_counter == 4){
    respiracao(255);
  }
  else if (effect_counter == 5){
    gradienteMovendo();
  }
  else if (effect_counter == 6){
    PixelsAleatorios();
  }
  else if (effect_counter == 7){
    bolasColoridas();
  }
  else if (effect_counter == 8){
    explosao();
  }
  else if (effect_counter == 9){
    circular(125);
  }
    else if (effect_counter == 10){
      raioArcoiris();
  }
  else if (effect_counter == 11){
    fillSolidColor(CRGB::Blue);
  }
  else if (effect_counter == 12){
    fillSolidColor(CRGB::DarkCyan);
  }
  else if (effect_counter == 13)
  {
    EEPROM.update(memory_adress, 0);
    resetFunc();
  }
}
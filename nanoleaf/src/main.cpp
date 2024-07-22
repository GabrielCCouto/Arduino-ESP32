#include <FastLED.h>
#include <EEPROM.h>
#include <time.h>
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
  if (effect_counter == 1){
    raioArcoirisCircular();
  }
  if (effect_counter == 2){
    gradienteOndas(5);
  }
  if (effect_counter == 3){
    gradienteOndas(1);
  }
  if (effect_counter == 4){
    gradienteOndas(2);
  }
  if (effect_counter == 5){
    gradienteOndas(3);
  }
  if (effect_counter == 6){
    gradienteOndas(4);
  }
  if (effect_counter == 7){
    gradienteOndas(6);
  }
  if (effect_counter == 8){
    gradienteOndas(7);
  }
  if (effect_counter == 9){
    gradienteOndas(8);
  }
  if (effect_counter == 10){
    gradienteOndas(9);
  }
  if (effect_counter == 11){
    gradienteOndas(10);
  }
  if (effect_counter == 12){
    gradienteOndas(11);
  }
  if (effect_counter == 13){
    srand(time(0));
    int random_number = rand() % 255;
    respiracao(random_number);
  }
  if (effect_counter == 14){
    srand(time(0));
    int random_number = rand() % 255;
    cometa(random_number);
  }
  if (effect_counter == 15){
    explosao();
  }
  if (effect_counter == 16){
    gradienteMovendo();
  }
  if (effect_counter == 17){
    srand(time(0));
    int random_number = rand() % 255;
    circular(random_number);
  }
  if (effect_counter == 18){
    fill_solid(fita, NUM_LEDS_FITA, CRGB::AliceBlue);
    FastLED.show();
  }
  if (effect_counter == 19){
    fill_solid(fita, NUM_LEDS_FITA, CRGB::Blue);
    FastLED.show();
  }
  if (effect_counter == 20){
    fill_solid(fita, NUM_LEDS_FITA, CRGB::DarkGreen);
    FastLED.show();
  }
  if (effect_counter == 21){
    fill_solid(fita, NUM_LEDS_FITA, CRGB::OrangeRed);
    FastLED.show();
  }
  if (effect_counter == 22){
    fill_solid(fita, NUM_LEDS_FITA, CRGB::DarkCyan);
    FastLED.show();
  }
  if (effect_counter == 23){
    fill_solid(fita, NUM_LEDS_FITA, CRGB::DarkRed);
    FastLED.show();
  }
  if (effect_counter == 24){
    fill_solid(fita, NUM_LEDS_FITA, CRGB::BlueViolet);
    FastLED.show();
  }
  if (effect_counter == 25){
    fill_solid(fita, NUM_LEDS_FITA, CRGB::LightGoldenrodYellow);
    FastLED.show();
  }
  if (effect_counter == 26){
    fill_solid(fita, NUM_LEDS_FITA, CRGB::DarkOrange);
    FastLED.show();
  }
  if (effect_counter == 27){
    fill_solid(fita, NUM_LEDS_FITA, CRGB::DarkRed);
    FastLED.show();
  }
  if (effect_counter == 28){
    fill_solid(fita, NUM_LEDS_FITA, CRGB::DarkViolet);
    FastLED.show();
  }
  if (effect_counter == 29)
  {
    EEPROM.update(memory_adress, 0);
    resetFunc();
  }
}
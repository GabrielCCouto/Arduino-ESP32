#include <FastLED.h>
#include <Arduino.h>
#include <Espalexa.h>
#include <FS.h>
#include <ESP8266mDNS.h>
#include "webServer.h"
#include "effects.h"

#define touch 12

// Variables to store the credentials
String wifiName = "";
String password = "";

// WiFiManager wifiManager;
Espalexa espalexa;
struct EffectsStatus EffectsStatus;

int effect_counter = 0;

void resetFunc() {
  ESP.restart();
}

void is_disable(struct EffectsStatus *status) {
  delay(500);
  if(digitalRead(touch) == HIGH) {
    effect_counter = -1;
    which_effect(DISABLE_LAMP, status);
    delay(500);
  }
}

IRAM_ATTR void pinTouch() {
  if (effect_counter == MAX_EFFECT){ effect_counter = -1; }
  write_effect(effect_counter + 1);
  effect_counter = read_effect();
  EffectsStatus.break_effect = true;
  EffectsStatus.current_effect = EffectsStatus.last_effect;
}

void setup() {
  Serial.begin(115200);
  pinMode(touch, INPUT);

  attachInterrupt(digitalPinToInterrupt(touch), pinTouch, FALLING);

  SPIFFS.begin();

  effect_counter = read_effect();

  FastLED.addLeds<WS2812, PINO_FITA, GRB>(fita, NUM_LEDS_FITA);
  FastLED.setBrightness(255);

  char uniqueID[25];
  char newID[25];
  sprintf(uniqueID, "%d", ESP.getChipId());
	strcat(strcpy(newID, "Iluminarium-"), uniqueID);

  espalexa.addDevice(newID, colorLightChanged);
  espalexa.begin();

  delay(800);
  if (digitalRead(touch) == HIGH) {
    Serial.println("Restart Wifi Config");
    write_effect(DISABLE_LAMP);
    // wifiManager.resetSettings();
    resetFunc();
  }
}

void loop() {
  if (EffectsStatus.current_effect == EffectsStatus.last_effect) {
    Serial.println("Change effect");
    EffectsStatus.current_effect = !EffectsStatus.last_effect; 
    EffectsStatus.break_effect = false;

    is_disable(&EffectsStatus);

    which_effect(effect_counter, &EffectsStatus);
    Serial.println(effect_counter);
  }
}

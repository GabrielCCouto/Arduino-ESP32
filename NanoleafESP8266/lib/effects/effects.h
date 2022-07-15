#ifndef __effects__
#define __effects__

#include <Arduino.h>
#include <FastLED.h>

#define NUM_LEDS_FITA 144
#define PINO_FITA 12

inline CRGB fita[NUM_LEDS_FITA];

void fillSolidColor(CRGB selcor);

void raioArcoiris();

void cometa(uint8_t color, int tipo);

#endif
#include <Arduino.h>
#include <FastLED.h>
#include "effects.h"


void fillSolidColor(CRGB selcor) {
  fill_solid(fita, NUM_LEDS_FITA, selcor);
  FastLED.show();
}

void raioArcoiris() {
  static uint8_t hue = 0;
  int dir1 = 0;
  int i1 = 0;

  for (int i = 0; i < 2000; i++) {
    fita[i1] = CHSV(hue++, 255, 255);

    FastLED.show();
    for (int i = 0; i < NUM_LEDS_FITA; i++) {
      fita[i].nscale8(250);
    }

    if (dir1 == 0) {
      i1++;
    } else {
      i1--;
    }
    if (i1 == NUM_LEDS_FITA) {
      dir1 = 1;
    } else if ( i1 == 0) {
      dir1 = 0;
    }
    delay(10);
  }
  fillSolidColor(CRGB::Black);
}

void cometa(uint8_t color, int tipo) {
  byte fade = 128;
  int cometaSize = 5;
  byte hue = color;
  int iDirection = 1;
  int iPos = 0;

  if (tipo == 1){
    byte hue = random(1, 255);
    for (int i = 0; i < 1000; i++) {
      iPos += iDirection;
      if (iPos == (NUM_LEDS_FITA - cometaSize) || iPos == 0)
        iDirection *= -1;

      for (int i = 0; i < cometaSize; i++)
        fita[iPos + i].setHue(hue);

      // Randomly fade the LEDs
      for (int j = 0; j < NUM_LEDS_FITA; j++)
        if (random(10) > 5)
          fita[j] = fita[j].fadeToBlackBy(fade);

      delay(20);
      FastLED.show();
    }
    fillSolidColor(CRGB::Black);
  }
}

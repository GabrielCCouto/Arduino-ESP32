#include "effects.h"

#define NUM_PALETTES 11

uint16_t breatheLevel = 0;
uint8_t palleteIndex = 0;

void fillSolidColor(CRGB selcor) {
  fill_solid(fita, NUM_LEDS_FITA, selcor);
  FastLED.show();
}

DEFINE_GRADIENT_PALETTE( fireandice_gp ) {
  0,  80,  2,  1,
  51, 206, 15,  1,
  101, 242, 34,  1,
  153,  16, 67, 128,
  204,   2, 21, 69,
  255,   1,  2,  4
};
CRGBPalette16 fireandicePalette = fireandice_gp;

DEFINE_GRADIENT_PALETTE( browngreen_gp ) {
  0,    6,  255,    0,     //green
  71,    0,  255,  153,     //bluegreen
  122,  200,  200,  200,     //gray
  181,  110,   61,    6,     //brown
  255,    6,  255,    0      //green
};
CRGBPalette16 brownGreenPalette = browngreen_gp;

DEFINE_GRADIENT_PALETTE( heatmap_gp ) {
  0,      0,    0,    0,  // black
  128,  255,    0,    0,  // red
  200,  255,  255,    0,  // bright yellow
  255,  255,  255,  255,  // full white
};
CRGBPalette16 heatPalette = heatmap_gp;

DEFINE_GRADIENT_PALETTE( greenblue_gp ) {
  0,    0,    255,    245,
  46,   0,    21,     255,
  179,  12,   250,    0,
  255,  0,    255,    245
};
CRGBPalette16 greenbluePalette = greenblue_gp;

DEFINE_GRADIENT_PALETTE( Sunset_Real_gp ) {
  0,    120,   0,    0,
  22,   179,   22,   0,
  51,   255,   104,  0,
  85,   167,   22,   18,
  135,  100,   0,    103,
  198,  16,    0,    130,
  255,  0,     0,    160
};
CRGBPalette16 sunsetPalette = Sunset_Real_gp;

DEFINE_GRADIENT_PALETTE( bhw2_turq_gp ) {
  0,   1, 33, 95,
  38,   1, 107, 37,
  76,  42, 255, 45,
  127, 255, 255, 45,
  178,  42, 255, 45,
  216,   1, 107, 37,
  255,   1, 33, 95
};
CRGBPalette16 turqPalette = bhw2_turq_gp;

DEFINE_GRADIENT_PALETTE( autumnrose_gp ) {
  0,  71,  3,  1,
  45, 128,  5,  2,
  84, 186, 11,  3,
  127, 215, 27,  8,
  153, 224, 69, 13,
  188, 229, 84,  6,
  226, 242, 135, 17,
  255, 247, 161, 79
};
CRGBPalette16 autumnrosePalette = autumnrose_gp;

DEFINE_GRADIENT_PALETTE( bhw1_06_gp ) {
  0, 184,  1, 128,
  160,   1, 193, 182,
  219, 153, 227, 190,
  255, 255, 255, 255
};
CRGBPalette16 bhw1_06Palette = bhw1_06_gp;

DEFINE_GRADIENT_PALETTE( bhw2_xmas_gp ) {
  0,   0, 12,  0,
  40,   0, 55,  0,
  66,   1, 117,  2,
  77,   1, 84,  1,
  81,   0, 55,  0,
  119,   0, 12,  0,
  153,  42,  0,  0,
  181, 121,  0,  0,
  204, 255, 12,  8,
  224, 121,  0,  0,
  244,  42,  0,  0,
  255,  42,  0,  0
};
CRGBPalette16 xmasPalette = bhw2_xmas_gp;

DEFINE_GRADIENT_PALETTE( bhw1_justducky_gp ) {
  0,  47, 28,  2,
  76, 229, 73,  1,
  163, 255, 255,  0,
  255, 229, 73,  1
};
CRGBPalette16 justduckyPalette = bhw1_justducky_gp;


CRGBPalette16 purplePalette = CRGBPalette16 (
                                CRGB::DarkViolet,
                                CRGB::DarkViolet,
                                CRGB::DarkViolet,
                                CRGB::DarkViolet,

                                CRGB::Magenta,
                                CRGB::Magenta,
                                CRGB::Linen,
                                CRGB::Linen,

                                CRGB::Magenta,
                                CRGB::Magenta,
                                CRGB::DarkViolet,
                                CRGB::DarkViolet,

                                CRGB::DarkViolet,
                                CRGB::DarkViolet,
                                CRGB::Linen,
                                CRGB::Linen
                              );

CRGBPalette16 returnPalette(int selPalette) {
  switch (selPalette) {
    case 1:
      return fireandice_gp;
      break;
    case 2:
      return browngreen_gp;
      break;
    case 3:
      return heatmap_gp;
      break;
    case 4:
      return greenblue_gp;
      break;
    case 5:
      return Sunset_Real_gp;
      break;
    case 6:
      return purplePalette;
      break;
    case 7:
      return bhw2_turq_gp;
      break;
    case 8:
      return autumnrose_gp;
      break;
    case 9:
      return bhw1_06_gp;
      break;
    case 10:
      return bhw2_xmas_gp;
      break;
    case 11:
      return bhw1_justducky_gp;
      break;
    default:
      return fireandice_gp;
      break;
  }
}

void gradienteOndas(int selPalette) {
  CRGBPalette16 Palette = returnPalette(selPalette);
  int indexPal = 2;
  for (int i = 0; i < 10000; i++) {
    byte beatA = beatsin16(30, 0, 255);
    byte beatB = beatsin16(20, 0, 255);
    fill_palette(fita, NUM_LEDS_FITA, (beatA + beatB) / 2, indexPal, Palette, 255, LINEARBLEND);
    FastLED.show();
    delay(10);
  }
}

void raioArcoiris() {
  static uint8_t hue = 0;
  int dir1 = 0;
  int i1 = 0;

  for (int i = 0; i < 10000; i++) {
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

void raioArcoirisCircular() {
  static uint8_t hue = 0;
  int i1 = 0;

  for (int i = 0; i < 10000; i++) {
    fita[i1] = CHSV(hue++, 255, 255);

    FastLED.show();
    for (int i = 0; i < NUM_LEDS_FITA; i++) {
      fita[i].nscale8(250);
    }
    i1++;
    if (i1 == NUM_LEDS_FITA) {
      i1 = 0;
    }
    delay(40);
  }
  fillSolidColor(CRGB::Black);
}

void cometa() {
  byte fade = 128;
  int random_color = random (50, 255);

  int cometaSize = 5;
  int iDirection = 1;
  int iPos = 0;

  for (int i = 0; i < 1000; i++) {
    iPos += iDirection;
    if (iPos == (NUM_LEDS_FITA - cometaSize) || iPos == 0)
      iDirection *= -1;

    for (int i = 0; i < cometaSize; i++)
      fita[iPos + i].setHue(random_color);

    // Randomly fade the LEDs
    for (int j = 0; j < NUM_LEDS_FITA; j++)
      if (random(10) > 5)
        fita[j] = fita[j].fadeToBlackBy(fade);
  delay(20);
  FastLED.show();
  }
  fillSolidColor(CRGB::Black);
}

void respiracao() {
  int random_color = random (15, 255);
  for (int i = 0; i < 1000; i++) {
    breatheLevel = beatsin16(10, 0, 255);
    fill_solid(fita, NUM_LEDS_FITA, CHSV(random_color, 255, breatheLevel));
    FastLED.show();
    delay(10);
  }
}

void gradienteMovendo() {
  CRGBPalette16 selPalette = returnPalette(random(1, NUM_PALETTES + 1));
  for (int i = 0; i < 10000; i++) {
    fill_palette(fita, NUM_LEDS_FITA, palleteIndex, 255 / NUM_LEDS_FITA, selPalette, 255, LINEARBLEND);
    FastLED.show();
    palleteIndex++;
    delay(10);
  }
}

void PixelsAleatorios() {
  CRGBPalette16 selPalette = returnPalette(random(1, NUM_PALETTES + 1));
  for (int i = 0; i < 1000; i++) {
    if (i % 5 == 0) {
      fita[random16(0, NUM_LEDS_FITA - 1)] = ColorFromPalette(selPalette, random8(), 255, LINEARBLEND);
    }
    fadeToBlackBy(fita, NUM_LEDS_FITA, 1);
    FastLED.show();
    delay(10);
  }
}

void bolasColoridas() {
  byte dothue = 0;
  for (int i = 0 ; i < 4000 ; i++) {
    fadeToBlackBy( fita, NUM_LEDS_FITA, 20);

    for ( int i = 0; i < 8; i++) {
      fita[beatsin16( i + 7, 0, NUM_LEDS_FITA - 1 )] |= CHSV(dothue, 200, 255);
      dothue += 32;
    }
    FastLED.show();
  }
}

void explosao() {
  FastLED.clear();
  byte fade = 128;
  int expSize = NUM_LEDS_FITA / 2;   // tamanho da explosao
  int numExplosoes = 4;         // quantas explosoes no efeito

  for (int x = 0; x < numExplosoes ; x++) {
    byte hue = random(1, 255);        // escolhe cor aleatoria

    for (int i = 0; i < expSize; i++) {
      fita[NUM_LEDS_FITA / 2 + i].setHue(hue);
      fita[NUM_LEDS_FITA / 2 - i].setHue(hue);
      if (i > expSize / 2) {
        i++;
        fita[NUM_LEDS_FITA / 2 + i].setHue(hue);
        fita[NUM_LEDS_FITA / 2 - i].setHue(hue);
      }
      FastLED.show();
    }

    delay(100);
    for (int i = 0; i < 400; i++) {
      for (int j = 0; j < NUM_LEDS_FITA; j++) {
        if (random(10) > 8)
          fita[j] = fita[j].fadeToBlackBy(fade);
      }
      delay(10);
      FastLED.show();
    }
  }
}

void circular() {
  int random_color = random (50, 255);
  int tamLuz = 6;
  int luzes[tamLuz];
  int luzesTemp;
  luzes[0] = 125;//CHSV(selcor, 255, 125);
  luzes[1] = 255;//CHSV(selcor, 255, 255);
  luzes[2] = 255;//CHSV(selcor, 255, 255);
  luzes[3] = 125;//CHSV(selcor, 255, 125);
  luzes[4] = 0;//CHSV(selcor, 255, 0);
  luzes[5] = 0;//CHSV(selcor, 255, 0);

  for (int i = 0; i < 500; i++) {

    for (int l = 0; l < NUM_LEDS_FITA; l = l + tamLuz) {
      for (int m = 0; m < tamLuz; m++) {
        fita[l + m] = CHSV(random_color, 255, luzes[m]);
      }
      FastLED.show();
    }

    luzesTemp = luzes[0];
    for (int n = 0; n < tamLuz - 1; n++) {
      luzes[n] = luzes[n + 1];
    }
    luzes[tamLuz - 1] = luzesTemp;

    delay(30);
  }
}
#include <FastLED.h>

#define NUM_LEDS_FITA 40
#define PINO_FITA 12
#define NUM_PALETTES 2

CRGB fita[NUM_LEDS_FITA];

// Cofig Respiracao
uint16_t breatheLevel = 0; 

// Cofig gradienteOndas
uint16_t beatA = 0;
uint16_t beatB = 0;

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

CRGBPalette16 returnPalette(int selPalette) {
  switch (selPalette) {
    case 1:
      return brownGreenPalette;
      break;
    case 2:
      return heatPalette;
      break;
    default:
      return heatPalette;
      break;
  }
}

void fillSolidColor(CRGB selcor) {
  fill_solid(fita, NUM_LEDS_FITA, selcor);
  FastLED.show();
}


void fullWhite(){
  fillSolidColor(CRGB::White);
  FastLED.show();
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


void respiracao(byte selcor, uint8_t velocidade) {
  switch (velocidade){
  case 1:
    velocidade = 10;
    break;
  case 2:
    velocidade = 30;
    break;
  case 3:
    velocidade = 50;
    break;
  default:
    velocidade = 10;
    break;
  }
  
  for (int i = 0; i < 1000; i++) {
    breatheLevel = beatsin16(velocidade, 0, 255);
    fill_solid(fita, NUM_LEDS_FITA, CHSV(selcor, 255, breatheLevel));
    FastLED.show();
    delay(10);
  }
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
  }
   
  if (tipo == 2){
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

void gradienteOndas() {
  CRGBPalette16 selPalette = returnPalette(random(1, NUM_PALETTES + 1));
  int indexPal = 2;
  for (int i = 0; i < 1000; i++) {
    beatA = beatsin16(30, 0, 255);
    beatB = beatsin16(20, 0, 255);
    fill_palette(fita, NUM_LEDS_FITA, (beatA + beatB) / 2, indexPal, selPalette, 255, LINEARBLEND);
    FastLED.show();
    delay(10);
  }
}
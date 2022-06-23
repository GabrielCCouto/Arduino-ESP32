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

DEFINE_GRADIENT_PALETTE( greenblue_gp ) {
  0,   0,  255, 245,
  46,  0,  21,  255,
  179, 12, 250, 0,
  255, 0,  255, 245
};
CRGBPalette16 greenbluePalette = greenblue_gp;

DEFINE_GRADIENT_PALETTE( Sunset_Real_gp ) {
  0, 120,  0,  0,
  22, 179, 22,  0,
  51, 255, 104,  0,
  85, 167, 22, 18,
  135, 100,  0, 103,
  198,  16,  0, 130,
  255,   0,  0, 160
};
CRGBPalette16 sunsetPalette = Sunset_Real_gp;

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

DEFINE_GRADIENT_PALETTE( fireandice_gp ) {
  0,  80,  2,  1,
  51, 206, 15,  1,
  101, 242, 34,  1,
  153,  16, 67, 128,
  204,   2, 21, 69,
  255,   1,  2,  4
};
CRGBPalette16 fireandicePalette = fireandice_gp;

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

CRGBPalette16 returnPalette(int selPalette) {
  switch (selPalette) {
    case 1:
      return brownGreenPalette;
      break;
    case 2:
      return heatPalette;
      break;
    case 3:
      return purplePalette;
      break;
    case 4:
      return greenbluePalette;
      break;
    case 5:
      return sunsetPalette;
      break;
    case 6:
      return fireandicePalette;
      break;
    case 7:
      return turqPalette;
      break;
    case 8:
      return autumnrosePalette;
      break;
    case 9:
      return bhw1_06Palette;
      break;
    case 10:
      return xmasPalette;
      break;
    case 11:
      return justduckyPalette;
      break;
    default:
      return heatPalette;
      break;
  }
}

void gradienteOndas(int tipo, int paleta) {
  CRGBPalette16 selPalette = returnPalette(NUM_PALETTES + 1);
  if (tipo == 1){
    CRGBPalette16 selPalette = returnPalette(random(1, NUM_PALETTES + 1));
  }else if (tipo == 2){
    CRGBPalette16 selPalette = returnPalette(paleta);
  }
  int indexPal = 2;
  for (int i = 0; i < 1000; i++) {
    beatA = beatsin16(30, 0, 255);
    beatB = beatsin16(20, 0, 255);
    fill_palette(fita, NUM_LEDS_FITA, (beatA + beatB) / 2, indexPal, selPalette, 255, LINEARBLEND);
    FastLED.show();
    delay(10);
  }
}

void fillSolidColor(CRGB selcor) {
  fill_solid(fita, NUM_LEDS_FITA, selcor);
  FastLED.show();
}


void fullWhite(){
  for(int i=0; i<1000; i++){
    fillSolidColor(CRGB::White);
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

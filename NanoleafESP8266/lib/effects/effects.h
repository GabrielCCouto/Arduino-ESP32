#ifndef __effects__
#define __effects__

#pragma once

#include <FastLED.h>

#define PINO_FITA 13
#define NUM_LEDS_FITA 24

#define DISABLE_LAMP 0
#define COLOR_RED 1
#define COLOR_BLUE 2
#define COLOR_GREEN 3
#define COLOR_WHITE 4
#define COLOR_DARK_ORANGE 5
#define COLOR_YELLOW 6
#define COLOR_DARK_VAIOLET 7

inline CRGB fita[NUM_LEDS_FITA];

void fillSolidColor(CRGB selcor);

void raioArcoiris();

void gradienteOndas(int selPalette);

void cometa();

void respiracao();

void gradienteMovendo();

void PixelsAleatorios();

void bolasColoridas();

void explosao();

void circular();

void raioArcoirisCircular();

#endif
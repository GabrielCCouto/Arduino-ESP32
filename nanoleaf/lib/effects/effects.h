#ifndef __effects__
#define __effects__

#include <Arduino.h>
#include <FastLED.h>

#define NUM_LEDS_FITA 39
#define PINO_FITA 12
#define NUM_PALETTES 2

inline CRGB fita[NUM_LEDS_FITA];

  /**
   * @brief
   *
   * Amethyst, AntiqueWhite, Aqua, Aquamarine, Azure, Beige, Bisque, Black, BlanchedAlmond
   * Blue, BlueViolet, Brown, BurlyWood, CadetBlue, Chartreuse, Chocolate, Coral, CornflowerBlue
   * Cornsilk, Crimson, Cyan, DarkBlue, DarkCyan ,DarkGoldenrod ,DarkGray ,DarkGrey, DarkGreen
   *
   * @param selcor Selecione uma cor para ficar estática (Mais cores em pixeltype.h)
   */
void fillSolidColor(CRGB selcor);

  /**
   * @brief
   * Faz um Arco iris
   */
void raioArcoiris();

  /**
   * @brief
   *
   * 1 - fireandice_gp, 2 - browngreen_gp, 3 - heatmap_gp 4 - greenblue_gp, 5 - Sunset_Real_gp
   * 6 - purplePalette, 7 - bhw2_turq_gp, 8 - autumnrose_gp - 9 bhw1_06_gp, 10 - bhw2_xmas_gp
   *
   * @param fileName Numero inteiro para selecionar as paletas
   */
void gradienteOndas(int selPalette);

  /**
   * @brief
   *
   * @param color Varia de 0 a 255
   *
   */
void cometa(uint8_t color);

#endif
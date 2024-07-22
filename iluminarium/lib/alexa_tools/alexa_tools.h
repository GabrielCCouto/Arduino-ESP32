#ifndef __ALEXA_TOOLS__
#define __ALEXA_TOOLS__

#pragma once

#include <fauxmoESP.h>

#define ID_RED              "vermelha"
#define ID_BLUE             "azul"
#define ID_GREEN            "verde"
#define ID_YELLOW           "amarelo"
#define ID_ORANGE_RED      "laranja"
#define ID_WHITE            "branco"
#define ID_DARK_VIOLET      "violeta"
#define ID_RAINBOW          "rainbow"
#define ID_FIRE_ICE         "fire ice"
#define ID_HEAT_MAP         "heat map"
#define ID_SUNSET           "sunset"
#define ID_COMETA           "cometa"

extern fauxmoESP fauxmo;

void device_IDs();

void which_effect_by_alexa(const char * device_name, bool state, int intensify);
void on_off_effect(int effect, bool state, int intensify);

#endif
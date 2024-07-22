#include "alexa_tools.h"
#include "effects.h"

void which_effect_by_alexa(const char * device_name, bool state, int intensify) {
  if (strcmp(device_name, ID_BLUE)==0)
  {
    on_off_effect(COLOR_BLUE, state, intensify);
  }
  else if (strcmp(device_name, ID_RED)==0)
  {
    on_off_effect(COLOR_RED, state, intensify);
  }
  else if (strcmp(device_name, ID_GREEN)==0)
  {
    on_off_effect(COLOR_GREEN, state, intensify);
  }
  else if (strcmp(device_name, ID_WHITE)==0)
  {
    on_off_effect(COLOR_WHITE, state, intensify);
  }
  else if (strcmp(device_name, ID_ORANGE_RED)==0)
  {
    on_off_effect(COLOR_ORANGE_RED, state, intensify);
  }
  else if (strcmp(device_name, ID_YELLOW)==0)
  {
    on_off_effect(COLOR_YELLOW, state, intensify);
  }
  else if (strcmp(device_name, ID_DARK_VIOLET)==0)
  {
    on_off_effect(COLOR_DARK_VAIOLET, state, intensify);
  }
  else if (strcmp(device_name, ID_RAINBOW)==0)
  {
    on_off_effect(RAINBOW, state, intensify);
  }
  else if (strcmp(device_name, ID_FIRE_ICE)==0)
  {
    on_off_effect(GRADIENT_FIRE_ICE, state, intensify);
  }
  else if (strcmp(device_name, ID_HEAT_MAP)==0)
  {
    on_off_effect(GRADIENT_HEAT_MAP, state, intensify);
  }
  else if (strcmp(device_name, ID_HEAT_MAP)==0)
  {
    on_off_effect(GRADIENT_SUNSET, state, intensify);
  }
}

void on_off_effect(int effect, bool state, int intensify) {
  FastLED.setBrightness(intensify);
  state ? write_effect(effect) : write_effect(DISABLE_LAMP);
}

void device_IDs() {
    fauxmo.addDevice(ID_RED);
    fauxmo.addDevice(ID_GREEN);
    fauxmo.addDevice(ID_BLUE);
    fauxmo.addDevice(ID_WHITE);
    fauxmo.addDevice(ID_ORANGE_RED);
    fauxmo.addDevice(ID_YELLOW);
    fauxmo.addDevice(ID_DARK_VIOLET);
    fauxmo.addDevice(ID_RAINBOW);
    fauxmo.addDevice(ID_FIRE_ICE); // ToDo Acredito que tenha limite pois se adicionar mais, não funciona...
    // fauxmo.addDevice(ID_HEAT_MAP);
    fauxmo.addDevice(ID_COMETA);
}


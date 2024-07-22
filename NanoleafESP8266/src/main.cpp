#include <FastLED.h>
#include <Arduino.h>
#include <FS.h>
#include "webServer.h"
#include "alexa_tools.h"
#include "effects.h"

#define touch 12

WiFiManager wifiManager;
fauxmoESP fauxmo;

int contador;
int memory_adress = 0;
int effect_counter = 0;
int led_off = 0;

void resetFunc() {
  ESP.restart();
}

IRAM_ATTR void pinTouch() {
  write_effect(effect_counter + 1);
  effect_counter = read_effect();
  // resetFunc();
}

void setup() {
  Serial.begin(115200);
  pinMode(touch, INPUT);

  // Initialize SPIFFS
  if (!SPIFFS.begin()) {
    Serial.println("Failed to initialize SPIFFS");
    return;
  }

  wifiManager.setAPCallback(configModeCallback);
  wifiManager.setSaveConfigCallback(saveConfigCallback);

  // wifiManager.resetSettings();
  wifiManager.autoConnect("Iluminarium", "12345678");

  delay(300);
  if (digitalRead(touch) == HIGH) {
    Serial.println("Update led_off");
    write_effect(DISABLE_LAMP);
    resetFunc();
  }

  effect_counter = read_effect();
  Serial.print("Effect Value: ");
  Serial.println(effect_counter);

  FastLED.addLeds<WS2812, PINO_FITA, GRB>(fita, NUM_LEDS_FITA);
  FastLED.setBrightness(100);
  attachInterrupt(digitalPinToInterrupt(touch), pinTouch, RISING);

  fauxmo.createServer(true);
  fauxmo.setPort(80);
  fauxmo.enable(true);
  device_IDs();

  fauxmo.onSetState([](unsigned char device_id, const char * device_name, bool state, unsigned char value) {
        Serial.printf("[MAIN] Device #%d (%s) state: %s value: %d\n", device_id, device_name, state ? "ON" : "OFF", value);
        if (strcmp(device_name, ID_BLUE)==0)
        {
          on_off_effect(COLOR_BLUE, state);
          effect_counter = read_effect();
        }
        if (strcmp(device_name, ID_RED)==0)
        {
          on_off_effect(COLOR_RED, state);
          effect_counter = read_effect();
        }
        if (strcmp(device_name, ID_GREEN)==0)
        {
          on_off_effect(COLOR_GREEN, state);
          effect_counter = read_effect();
        }
        if (strcmp(device_name, ID_WHITE)==0)
        {
          on_off_effect(COLOR_WHITE, state);
          effect_counter = read_effect();
        }
        if (strcmp(device_name, ID_DARK_ORANGE)==0)
        {
          on_off_effect(COLOR_DARK_ORANGE, state);
          effect_counter = read_effect();
        }
        if (strcmp(device_name, ID_YELLOW)==0)
        {
          on_off_effect(COLOR_YELLOW, state);
          effect_counter = read_effect();
        }
        if (strcmp(device_name, ID_DARK_VIOLET)==0)
        {
          on_off_effect(COLOR_DARK_VAIOLET, state);
          effect_counter = read_effect();
        }
    });
}

void loop() {
  fauxmo.handle();
  switch (effect_counter) {
    case DISABLE_LAMP:
      fillSolidColor(CRGB::Black);
      break;
    case COLOR_RED:
      fillSolidColor(CRGB::Red);
      break;
    case COLOR_BLUE:
      fillSolidColor(CRGB::Blue);
      break;
    case COLOR_GREEN:
      fillSolidColor(CRGB::Green);
      break;
    case COLOR_WHITE:
      fillSolidColor(CRGB::White);
      break;
    case COLOR_DARK_ORANGE:
      fillSolidColor(CRGB::DarkOrange);
      break;
    case COLOR_YELLOW:
      fillSolidColor(CRGB::Yellow);
      break;
    case COLOR_DARK_VAIOLET:
      fillSolidColor(CRGB::DarkViolet);
      break;
    default:
      fillSolidColor(CRGB::Black);
      write_effect(DISABLE_LAMP);
      effect_counter = 0;
      break;
  }
}

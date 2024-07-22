#ifndef __webServer_H__
#define __webServer_H__

#pragma once

#include "Espalexa.h"

void config_wifi();

// void configModeCallback (WiFiManager *myWiFiManager);

void saveConfigCallback();

void init_wifi_ap();

bool init_wifi_sta(String SSID, String PASSWORD);

void create_web_server();

void configure_setup_server_routes(AsyncWebServer *server);

void saveCredentialsToSPIFFS(String wifiName, String password);

void readCredentialsFromSPIFFS(String &wifiName, String &password);

#endif
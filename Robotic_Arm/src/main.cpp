#include <Wire.h>
#include <Arduino.h>
#include "AS5600.h"
#include "MagneticEncoder.h"  // Nova biblioteca que criamos

#define SDA_PIN 14
#define SCL_PIN 15

#define STEP_PIN 2
#define DIR_PIN 3

TwoWire myWire(SDA_PIN, SCL_PIN);
AMS_5600 ams5600(myWire);

float gearRatio = 12.3;
MagneticEncoder encoder(ams5600, STEP_PIN, DIR_PIN, 1.5, 0.01, 0.1);

float targetAngle = 90.0; // alvo inicial

void setup() {
  Serial.begin(115200);
  while (!Serial);
  myWire.begin();

  delay(1000);
  if (myWire.endTransmission() == 0) {
    Serial.println("AMS5600 detectado!");
  } else {
    Serial.println("AMS5600 NÃO detectado!");
  }

  // Define ângulo alvo inicial
  encoder.setTargetAngle(targetAngle);
  Serial.println("Controle PID iniciado. Alvo = 90 graus.");
}

void loop() {
  // Atualiza o controle em tempo real
  encoder.update();

  // (Opcional) Imprime status a cada meio segundo
  static unsigned long lastPrint = 0;
  if (millis() - lastPrint > 500) {
    float current = encoder.getCurrentAngle();
    float error = encoder.getError();
    Serial.print("Ângulo atual: ");
    Serial.print(current, 2);
    Serial.print(" | Erro: ");
    Serial.println(error, 2);
    lastPrint = millis();
  }
}

#include <Arduino.h>

// --- Configuração dos motores (6 motores) ---

const int stepPins[6] = {2, 5, 8, 11, 14, 17};
const int dirPins[6]  = {3, 6, 9, 12, 15, 18};
const int enPins[6]   = {4, 7, 10, 13, 16, 19};

const float stepsPerRev = 200;     // full steps
const int microsteps = 16;
const float reductionRatio = 12.15;
const float stepsPerDegree = (stepsPerRev * microsteps * reductionRatio) / 360.0;

float currentAngles[6] = {0};  // Guarda o ângulo atual de cada motor

void setupMotor(int i) {
  pinMode(stepPins[i], OUTPUT);
  pinMode(dirPins[i], OUTPUT);
  pinMode(enPins[i], OUTPUT);
  digitalWrite(enPins[i], LOW); // Ativa driver
}

void moveToAngle(int motorIndex, float targetAngle) {
  float delta = targetAngle - currentAngles[motorIndex];
  bool direction = delta >= 0;
  int steps = abs(delta * stepsPerDegree);

  digitalWrite(dirPins[motorIndex], direction ? HIGH : LOW);

  for (int i = 0; i < steps; i++) {
    digitalWrite(stepPins[motorIndex], HIGH);
    delayMicroseconds(100);
    digitalWrite(stepPins[motorIndex], LOW);
    delayMicroseconds(100);
  }

  currentAngles[motorIndex] = targetAngle;
}

void setup() {
  Serial.begin(115200);
  for (int i = 0; i < 6; i++) {
    setupMotor(i);
  }
  Serial.println("Sistema pronto para receber comandos.");
}

void loop() {
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    input.trim();

    if (input.startsWith("M")) {
      int motorIndex = input.substring(1, 2).toInt() - 1;
      float angle = input.substring(3).toFloat();
      if (motorIndex >= 0 && motorIndex < 6) {
        Serial.print("Movendo motor ");
        Serial.print(motorIndex + 1);
        Serial.print(" para ");
        Serial.print(angle);
        Serial.println(" graus");
        moveToAngle(motorIndex, angle);
        Serial.println("OK");
      } else {
        Serial.println("Motor inválido");
      }
    } else if (input.startsWith("J")) {
      input.remove(0, 2);  // remove "J "
      for (int i = 0; i < 6; i++) {
        int spaceIndex = input.indexOf(' ');
        String angleStr = (spaceIndex == -1) ? input : input.substring(0, spaceIndex);
        float angle = angleStr.toFloat();
        moveToAngle(i, angle);
        input = (spaceIndex == -1) ? "" : input.substring(spaceIndex + 1);
      }
      Serial.println("OK");
    } else {
      Serial.println("Comando desconhecido.");
    }
  }
}

// Versão aprimorada do controle PID para motor com AS5600
// Compatível com PlatformIO usando a biblioteca PID de br3ttb

#include <Wire.h>
#include <Arduino.h>
#include <PID_v1.h>
#include "AS5600.h"

#define SDA_PIN 14
#define SCL_PIN 15

#define STEP_PIN 2
#define DIR_PIN 3

// PID tunings
#define KP 7.5
#define KI 0.0
#define KD 0.0

TwoWire myWire(SDA_PIN, SCL_PIN);
AMS_5600 ams5600(myWire);

float gearRatio = 12.3;
float targetAngle = 270.0;  // Alvo em graus na saída final (eixo reduzido)

// PID Variables
double input = 0, output = 0, setpoint = 0;
PID pid(&input, &output, &setpoint, KP, KI, KD, DIRECT);

// Controle de voltas
long turns = 0;
float lastAngle = 0.0;

// Função para ler o ângulo absoluto com contagem de voltas
float getTotalAngle() {
  word raw = ams5600.getRawAngle(); // 0–4095
  float angle = raw * 0.087890625;  // 360 / 4096 = 0.087890625

  // Corrige transição 360 -> 0 e vice-versa
  float delta = angle - lastAngle;
  if (delta > 180.0) turns--;
  else if (delta < -180.0) turns++;

  lastAngle = angle;
  return turns * 360.0 + angle;  // Grau absoluto com voltas acumuladas
}

// Função de controle do motor via step/dir
void stepMotor(bool direction, int steps, int stepDelay) {
  digitalWrite(DIR_PIN, direction);
  for (int i = 0; i < steps; i++) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(stepDelay);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(stepDelay);
  }
}

void setup() {
  Serial.begin(115200);
  myWire.begin();

  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);

  delay(1500);

  if (ams5600.detectMagnet()) {
    Serial.println("AMS5600 detectado!");
  } else {
    Serial.println("AMS5600 NAO detectado!");
  }

  setpoint = targetAngle * gearRatio;  // Alvo em graus no eixo do motor
  pid.SetMode(AUTOMATIC);
  pid.SetOutputLimits(-10, 10);  // Saída: nº de steps por ciclo

  Serial.print("Controle PID iniciado. Alvo = ");
  Serial.print(targetAngle);
  Serial.println(" graus na saída.");
}

void loop() {
  // Atualiza entrada PID
  input = getTotalAngle();
  pid.Compute();

  if (abs(setpoint - input) >= 0.1) {
    int steps = constrain(abs(output), 1, 10);
    int stepDelay = map(abs(output), 1, 10, 100, 30);  // Delay reduz conforme erro aumenta
    bool dir = output > 0;
    stepMotor(dir, steps, stepDelay);
  }

  // Checa comandos pela Serial
  if (Serial.available()) {
    String inputStr = Serial.readStringUntil('\n');
    inputStr.trim();
    if (inputStr.startsWith("set ")) {
      float newTarget = inputStr.substring(4).toFloat();
      if (newTarget >= 0 && newTarget <= 360) {
        targetAngle = newTarget;
        setpoint = targetAngle * gearRatio;
        Serial.print("Novo alvo: ");
        Serial.println(targetAngle);
      } else {
        Serial.println("Erro: alvo fora do intervalo 0–360");
      }
    } else {
      Serial.println("Comando invalido. Use: set <graus>");
    }
  }

  // Debug
  static unsigned long lastPrint = 0;
  if (millis() - lastPrint > 500) {
    Serial.print("Atual: "); Serial.print(input / gearRatio, 2);
    Serial.print(" | Alvo: "); Serial.print(targetAngle);
    Serial.print(" | Erro: "); Serial.print((setpoint - input) / gearRatio);
    Serial.print(" | Saida PID: "); Serial.println(output);
    lastPrint = millis();
  }
}

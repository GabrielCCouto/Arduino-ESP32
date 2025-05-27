#include <Wire.h>
#include <Arduino.h>
#include <PID_v1.h>
#include "AS5600.h"

#define SDA_PIN 14
#define SCL_PIN 15

#define STEP_PIN 2
#define DIR_PIN 3

// PID tunings
#define KP 4.0
#define KI 0.15
#define KD 0.6

TwoWire myWire(SDA_PIN, SCL_PIN);
AMS_5600 ams5600(myWire);

float gearRatio = 12.3;
float targetAngle = 200.0;  // Alvo em graus na saída final (eixo reduzido)

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

  if (abs(setpoint - input) >= 0.5) {
    float outputAbs = abs(output);

    // Passos: pode começar com mais força
    int steps = map(outputAbs, 0, 10, 1, 10);
    steps = constrain(steps, 1, 10);

    // Delay inversamente proporcional ao erro
    int stepDelay = map(outputAbs, 0, 10, 300, 50);  // rápido no início, lento no fim
    stepDelay = constrain(stepDelay, 50, 300);

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
  // Plot PID - a cada 50ms
  static unsigned long lastPlot = 0;
  if (millis() - lastPlot > 50) {
    // Primeira linha opcional: cabeçalhos para o Arduino Plotter
    static bool headerPrinted = false;
    if (!headerPrinted) {
      Serial.println("Leitura\tAlvo");
      headerPrinted = true;
    }

    float leituraSaida = input / gearRatio;  // Converte de graus do motor para a saída
    Serial.print(leituraSaida);
    Serial.print("\t");
    Serial.print(targetAngle);
    Serial.print("\t");
    Serial.print(195.0); // Fixa o mínimo do eixo Y
    Serial.print("\t");
    Serial.println(205.0); // Fixa o máximo
    lastPlot = millis();
  }
}

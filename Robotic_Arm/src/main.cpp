#include <Arduino.h>
#include <TMCStepper.h>

// Defina os pinos para Step, Dir e a comunicação UART
#define STEP_PIN 2   // Conecte ao pino STEP do TMC2208
#define DIR_PIN 3    // Conecte ao pino DIR do TMC2208
#define EN_PIN 4     // Pino de Enable do driver TMC2208
#define SERIAL_PORT Serial  // Usando a Serial padrão para comunicação UART

// Parâmetros do motor e redução
const int stepsPerRevolution = 200;  // Número de passos para 1 rotação completa do motor no modo full step
const int microstepSetting = 16;    // Configuração de micropassos via UART (16 micropassos)
const float reductionRatio = 12.15;       // Relação de redução da caixa de engrenagens

// Número total de passos necessários para 1 volta na saída da caixa de redução
const int totalSteps = stepsPerRevolution * microstepSetting * reductionRatio;

// Defina a corrente máxima (em miliamperes) e outras configurações
#define CURRENT 800   // Corrente de operação (mA)
#define R_SENSE 0.11  // Valor do resistor de sense (Ω)

// Inicializa o driver TMC2208
TMC2208Stepper driver(&SERIAL_PORT, R_SENSE);  // Driver TMC2208 usando Serial padrão

void setup() {
  // Configuração de pinos
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(EN_PIN, OUTPUT);
  digitalWrite(EN_PIN, LOW);  // Habilita o driver TMC2208

  // Inicializa a comunicação serial
  SERIAL_PORT.begin(115200);

  // Configura o driver TMC2208
  driver.begin();                // Inicializa o driver
  driver.toff(5);                // Configura o tempo de desligamento
  driver.rms_current(CURRENT);    // Configura a corrente RMS do motor
  driver.microsteps(microstepSetting);  // Configura os micropassos (16 micropassos)

  // Depuração
  Serial.begin(9600);
  Serial.println("Iniciando o controle do motor de passo com TMC2208...");
}

// Função para mover o motor
void moveMotor(int steps, bool direction) {
  digitalWrite(DIR_PIN, direction ? HIGH : LOW);  // Define a direção do motor
  
  for (int i = 0; i < steps; i++) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(100);  // Ajuste o delay conforme necessário
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(100);  // Ajuste o delay conforme necessário
    Serial.print("Passo: ");
    Serial.println(i + 1);
  }
}

void loop() {
  // Gira o motor 1 volta no sentido horário
  Serial.println("Girando 1 volta no sentido horário");
  Serial.print("totalSteps = ");
  Serial.println(totalSteps);
  moveMotor(totalSteps, true);  // Sentido horário
  
  delay(2000);  // Pausa de 2 segundos

  // Gira o motor 1 volta no sentido anti-horário
  Serial.println("Girando 1 volta no sentido anti-horário");
  Serial.print("totalSteps = ");
  Serial.println(totalSteps);
  moveMotor(totalSteps, false);  // Sentido anti-horário
  
  delay(2000);  // Pausa de 2 segundos
}

#include "MagneticEncoder.h"

MagneticEncoder::MagneticEncoder(AMS_5600& sensor, int stepPin, int dirPin, float kp, float ki, float kd)
  : _sensor(&sensor), _stepPin(stepPin), _dirPin(dirPin),
    _kp(kp), _ki(ki), _kd(kd),
    _targetAngle(0), _error(0), _lastError(0), _integral(0), _lastUpdateTime(0) {

  pinMode(_stepPin, OUTPUT);
  pinMode(_dirPin, OUTPUT);
}

void MagneticEncoder::setTargetAngle(float angleDeg) {
  _targetAngle = angleDeg;
}

float MagneticEncoder::getCurrentAngle() {
  word raw = _sensor->getRawAngle();     // 0-4095
  return raw * 0.087890625;              // converte para graus
}

float MagneticEncoder::getError() {
  return _error;
}

void MagneticEncoder::stepMotor(bool direction) {
  digitalWrite(_dirPin, direction);
  digitalWrite(_stepPin, HIGH);
  delayMicroseconds(200);   // ajuste conforme necessário
  digitalWrite(_stepPin, LOW);
  delayMicroseconds(200);
}

void MagneticEncoder::update() {
  unsigned long now = millis();
  float dt = (now - _lastUpdateTime) / 1000.0; // em segundos
  if (dt <= 0) return;

  _currentAngle = getCurrentAngle();
  _error = _targetAngle - _currentAngle;

  // Corrige erro circular (360 -> 0 wraparound)
  if (_error > 180) _error -= 360;
  if (_error < -180) _error += 360;

  float derivative = (_error - _lastError) / dt;
  _integral += _error * dt;

  float output = _kp * _error + _ki * _integral + _kd * derivative;

  // Decide direção e passos
  if (abs(output) > 0.5) {  // tolerância mínima
    bool direction = output > 0;
    stepMotor(direction);
  }

  _lastError = _error;
  _lastUpdateTime = now;
}

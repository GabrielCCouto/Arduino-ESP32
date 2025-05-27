#ifndef MAGNETIC_ENCODER_H
#define MAGNETIC_ENCODER_H

#include <Arduino.h>
#include <AS5600.h>

class MagneticEncoder {
public:
  MagneticEncoder(AMS_5600& sensor, int stepPin, int dirPin, float kp, float ki, float kd, float gearRatio = 1.0);

  void setTargetAngle(float angleDeg);   // em graus
  void update();                         // chama em loop()

  float getCurrentAngle();               // leitura atual
  float getError();                      // erro atual

private:
  AMS_5600* _sensor;
  int _stepPin, _dirPin;

  float _gearRatio;
  long _turns = 0;
  float _lastRawAngle = 0.0;

  float _targetAngle;
  float _currentAngle;
  float _error;
  float _lastError;
  float _integral;

  float _kp, _ki, _kd;

  unsigned long _lastUpdateTime;

  void stepMotor(bool direction, int steps, int stepDelay);
};

#endif

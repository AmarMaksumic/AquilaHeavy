#include <Arduino.h>
#include <Servo.h>

Servo servoY;
const float PY = 3;
const float IY = 0;
const float DY = 0.001;
long previousTimeY = 0;
float lastErrorY, cumulativeErrorY = 0;

void reset_servoY() {
  servoY.write(107);
}

void init_servoY(int pin) {
  servoY.attach(pin);
  reset_servoY();
}

float align_servoY(float yTilt, float setPoint) {
  long currentTime = millis();
  long elapsedTime = currentTime - previousTimeY;

  float error = setPoint - yTilt;

  cumulativeErrorY += error * elapsedTime;

  float rateError = (error - lastErrorY) / elapsedTime;

  float output = PY * error + IY * cumulativeErrorY + DY * rateError;

  lastErrorY = error;
  previousTimeY = currentTime;

  output = 107 + (output*2);

  if (output > 142) output = 142;
  if (output < 72) output = 72;

  Serial.println(output);

  servoY.write(output);

  return output;
}

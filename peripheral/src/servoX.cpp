#include <Arduino.h>
#include <Servo.h>

Servo servoX;
const float PX = 3;
const float IX = 0;
const float DX = 0.001;
long previousTimeX = 0;
float lastErrorX, cumulativeErrorX = 0;

void reset_servoX() {
  servoX.write(89);
}

void init_servoX(int pin) {
  servoX.attach(pin);
  reset_servoX();
}

float align_servoX(float xTilt, float setPoint) {
  long currentTime = millis();
  long elapsedTime = currentTime - previousTimeX;

  float error = setPoint - xTilt;

  cumulativeErrorX += error * elapsedTime;

  float rateError = (error - lastErrorX) / elapsedTime;

  float output = PX * error + IX * cumulativeErrorX + DX * rateError;

  lastErrorX = error;
  previousTimeX = currentTime;

  output = 89 + (output*2);

  if (output > 119) output = 119;
  if (output < 59) output = 59;

  Serial.println(output);

  servoX.write(output);

  return output;
}

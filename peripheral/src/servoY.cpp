#include <Arduino.h>
#include <Servo.h>

class servoY {
  Servo servo;
  int pos = 0;
  const float P = 1;
  const float I = 1;
  const float D = 1;
  long previousTime = 0;
  float lastError, cumulativeError = 0;

  public:

    void init(int pin) {
      servo.attach(pin);
    }

    void align(float yTilt, float setPoint) {
      long currentTime = millis();
      long elapsedTime = currentTime - previousTime;

      float error = setPoint - yTilt;

      cumulativeError += error * elapsedTime;

      float rateError = (error - lastError) / elapsedTime;

      float output = P * error + I * cumulativeError + D * rateError;

      lastError = error;
      previousTime = currentTime;

      servo.write(output);
    }
};

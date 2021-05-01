#include <Arduino.h>
#include <servoX.hpp>
#include <servoY.hpp>
#include <gyro.hpp>
#include <SoftwareSerial.h>

SoftwareSerial softSerial(10, 11);
float test_vals[5] = {0, -2.14, 2.06, -5.345, 5.038};

int time_step = 0;

void setup() {
  Serial.begin(9600);
  softSerial.begin(9600);
  init_gyro();
  init_servoX(8);
  init_servoY(9);
}

float * update_test() {
  static float euler[3] = {test_vals[1], 1, 0};
  return euler;
}

void loop() {
  float *gyro_vals;
  gyro_vals = update_gyro();
  float x_out = align_servoX(*(gyro_vals + 2) * 180/M_PI, 0);
  float y_out = align_servoY(*(gyro_vals + 0) * 180/M_PI, 0);
  delay(25);
}

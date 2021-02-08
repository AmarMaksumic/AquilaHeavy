#include <Arduino.h>
#include <servoX.hpp>
#include <servoY.hpp>
#include <gyro.hpp>

servoX x;
servoY y;
gyro greek;
float setPoint = 0;

void setup() {
  x.init(9);
  y.init(10);
  greek.init();
  Serial.begin(9600);
  Serial.println('HI! I WILL SEND U DATA B!');
}

void loop() {
  greek.update();
  int ax = greek.get_acc_x(), 
  ay = greek.get_acc_y(), 
  az = greek.get_acc_z(), 
  gx = greek.get_gyro_x(), 
  gy = greek.get_gyro_y(), 
  gz = greek.get_gyro_z();
  x.align(gx, 0);
  y.align(gy, 0);
  String data = "ax " + String(ax) + " ay " + String(ay) + " az " + String(az) + " gx " + String(gx) + " gy " + String(gy) + " gz " + String(gz); 
  Serial.println(data);
}
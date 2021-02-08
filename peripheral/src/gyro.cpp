#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050.h>

class gyro {

  MPU6050 mpu;
  int16_t ax, ay, az;
  int16_t gx, gy, gz;

  public:

    void init() {
      if (I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE) Wire.begin();
      // else if (I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE) Fastwire::setup(400, true);
      mpu.initialize();
    }

    void update() {
      mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    }

    int get_acc_x() {
      return ax;
    }

    int get_acc_y() {
      return ay;
    }

    int get_acc_z() {
      return az;
    }

    int get_gyro_x() {
      return gx;
    }

    int get_gyro_y() {
      return gy;
    }

    int get_gyro_z() {
      return gz;
    }
};

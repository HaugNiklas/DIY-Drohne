#include <Arduino.h>
#include "MPU6050.h"

MPU6050 imu(5, 6); // SDA=5, SCL=6

void setup()
{
  Serial.begin(115200);

  if (!imu.begin())
  {
    Serial.println("FEHLER: MPU-6050 nicht gefunden!");
    while (1)
      ;
  }
  Serial.println("MPU-6050 bereit!");
}

void loop()
{
  imu.update();

  Serial.print("Roll: ");
  Serial.print(imu.getRoll(), 1);
  Serial.print("°  Pitch: ");
  Serial.print(imu.getPitch(), 1);
  Serial.println("°");

  delay(10);
}
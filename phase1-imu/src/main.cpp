#include <Arduino.h>
#include "MPU6050.h"

MPU6050 imu(5, 6);

void setup()
{
  Serial.begin(115200);
  if (!imu.begin())
  {
    Serial.println("FEHLER: MPU-6050 nicht gefunden!");
    while (1)
      ;
  }
  Serial.println("Kalibrierung – Board flach hinlegen!");
  delay(3000);
  Serial.println("Messe...");
  imu.calibrate(500);
  Serial.println("Fertig!");
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
#include <Arduino.h>
#include "MPU6050.h"

MPU6050::MPU6050(uint8_t sdaPin, uint8_t sclPin)
    : _sda(sdaPin), _scl(sclPin) {}

bool MPU6050::begin()
{
    Wire.begin(_sda, _scl);

    Wire.beginTransmission(ADDR);
    Wire.write(0x6B);
    Wire.write(0x00);
    if (Wire.endTransmission() != 0)
        return false;

    _letzteZeit = millis();
    return true;
}

void MPU6050::leseRohdaten()
{
    Wire.beginTransmission(ADDR);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(ADDR, (uint8_t)14);

    int16_t ax = Wire.read() << 8 | Wire.read();
    int16_t ay = Wire.read() << 8 | Wire.read();
    int16_t az = Wire.read() << 8 | Wire.read();
    Wire.read(); Wire.read(); // Temperatur
    int16_t gx = Wire.read() << 8 | Wire.read();
    int16_t gy = Wire.read() << 8 | Wire.read();
    Wire.read(); Wire.read(); // gz

    // Skalieren + Offsets abziehen → in Klassenvariablen speichern
    _ax = ax * ACCEL_SCALE - _offAx;
    _ay = ay * ACCEL_SCALE - _offAy;
    _az = az * ACCEL_SCALE - _offAz;
    _gx = gx * GYRO_SCALE  - _offGx;
    _gy = gy * GYRO_SCALE  - _offGy;
}

void MPU6050::calibrate(uint16_t samples)
{
    double sumAx = 0, sumAy = 0, sumAz = 0;
    double sumGx = 0, sumGy = 0;

    for (uint16_t i = 0; i < samples; i++)
    {
        Wire.beginTransmission(ADDR);
        Wire.write(0x3B);
        Wire.endTransmission(false);
        Wire.requestFrom(ADDR, (uint8_t)14);

        int16_t ax = Wire.read() << 8 | Wire.read();
        int16_t ay = Wire.read() << 8 | Wire.read();
        int16_t az = Wire.read() << 8 | Wire.read();
        Wire.read(); Wire.read();
        int16_t gx = Wire.read() << 8 | Wire.read();
        int16_t gy = Wire.read() << 8 | Wire.read();
        Wire.read(); Wire.read();

        sumAx += ax * ACCEL_SCALE;
        sumAy += ay * ACCEL_SCALE;
        sumAz += az * ACCEL_SCALE;
        sumGx += gx * GYRO_SCALE;
        sumGy += gy * GYRO_SCALE;

        delay(2);
    }

    _offAx = sumAx / samples;
    _offAy = sumAy / samples;
    _offAz = sumAz / samples - 1.0f; // Schwerkraft abziehen
    _offGx = sumGx / samples;
    _offGy = sumGy / samples;

    Serial.print("Offset aX="); Serial.print(_offAx, 4);
    Serial.print(" aY="); Serial.print(_offAy, 4);
    Serial.print(" aZ="); Serial.print(_offAz, 4);
    Serial.print(" gX="); Serial.print(_offGx, 4);
    Serial.print(" gY="); Serial.println(_offGy, 4);
}

void MPU6050::update()
{
    leseRohdaten();

    unsigned long jetzt = millis();
    float dt = (jetzt - _letzteZeit) / 1000.0f;
    _letzteZeit = jetzt;

    if (dt <= 0.0f || dt > 0.5f)
        dt = 0.01f;

    float rollAcc  = atan2f(_ay, _az) * 180.0f / M_PI;
    float pitchAcc = atan2f(-_ax, sqrtf(_ay * _ay + _az * _az)) * 180.0f / M_PI;

    _roll  = ALPHA * (_roll  + _gx * dt) + (1.0f - ALPHA) * rollAcc;
    _pitch = ALPHA * (_pitch + _gy * dt) + (1.0f - ALPHA) * pitchAcc;
}
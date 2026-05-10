#include "MPU6050.h"

MPU6050::MPU6050(uint8_t sdaPin, uint8_t sclPin)
    : _sda(sdaPin), _scl(sclPin) {}

bool MPU6050::begin()
{
    Wire.begin(_sda, _scl);

    // MPU aufwecken
    Wire.beginTransmission(ADDR);
    Wire.write(0x6B);
    Wire.write(0x00);
    if (Wire.endTransmission() != 0)
    {
        return false; // Kein Gerät gefunden
    }

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
    Wire.read();
    Wire.read(); // Temperatur überspringen
    int16_t gx = Wire.read() << 8 | Wire.read();
    int16_t gy = Wire.read() << 8 | Wire.read();
    Wire.read();
    Wire.read(); // gz überspringen

    _ax = ax * ACCEL_SCALE;
    _ay = ay * ACCEL_SCALE;
    _az = az * ACCEL_SCALE;
    _gx = gx * GYRO_SCALE;
    _gy = gy * GYRO_SCALE;
}

void MPU6050::update()
{
    leseRohdaten();

    unsigned long jetzt = millis();
    float dt = (jetzt - _letzteZeit) / 1000.0f;
    _letzteZeit = jetzt;

    if (dt <= 0.0f || dt > 0.5f)
        dt = 0.01f;

    float rollAcc = atan2f(_ay, _az) * 180.0f / M_PI;
    float pitchAcc = atan2f(-_ax, sqrtf(_ay * _ay + _az * _az)) * 180.0f / M_PI;

    _roll = ALPHA * (_roll + _gx * dt) + (1.0f - ALPHA) * rollAcc;
    _pitch = ALPHA * (_pitch + _gy * dt) + (1.0f - ALPHA) * pitchAcc;
}
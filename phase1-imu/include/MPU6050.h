#pragma once
#include <Wire.h>
#include <math.h>

class MPU6050
{
public:
    // Konstruktor
    MPU6050(uint8_t sdaPin = 5, uint8_t sclPin = 6);

    // Öffentliche Methoden
    bool begin();
    void update();

    float getRoll() const { return _roll; }
    float getPitch() const { return _pitch; }
    float getGyroX() const { return _gx; }
    float getGyroY() const { return _gy; }
    float getGyroZ() const { return _gz; }

private:
    // I2C Pins
    uint8_t _sda, _scl;

    // Rohdaten
    float _ax, _ay, _az;
    float _gx, _gy, _gz;

    // Winkel
    float _roll = 0;
    float _pitch = 0;

    // Timing
    unsigned long _letzteZeit = 0;

    // Konstanten
    static constexpr uint8_t ADDR = 0x68;
    static constexpr float ACCEL_SCALE = 1.0f / 16384.0f;
    static constexpr float GYRO_SCALE = 1.0f / 131.0f;
    static constexpr float ALPHA = 0.98f;

    // Private Hilfsmethode
    void leseRohdaten();
};
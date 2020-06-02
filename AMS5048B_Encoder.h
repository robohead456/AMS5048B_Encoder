#pragma once

#include <Arduino.h>
#include <Wire.h>

class AMS5048B_Encoder {
    public:
        AMS5048B_Encoder(uint8_t address, bool invertDir = false);
        float readAngle();
        void calibrate();
        void calibrate(float cal);

    private:
        bool invertDir;
        uint8_t address;
        float calibration = 0;
        const float RAD_PER_TICK = (2*PI/16384.0f);
        uint16_t readAngleRaw_tick();
        float readAngleRaw_rad();

};
#include "AMS5048B_Encoder.h"

AMS5048B_Encoder::AMS5048B_Encoder(uint8_t address, bool invertDir) {
    this->address = address;
    this->invertDir = invertDir;
}

float AMS5048B_Encoder::readAngle() {
    float val = (this->readAngleRaw_rad() - calibration);
    if(val < 0) val += 2*PI;
    if(val >= 2*PI) val -= 2*PI;

    if(val > PI)  val -= 2*PI;

    if(invertDir) return -val;
    return val;
}

void AMS5048B_Encoder::calibrate() {
    calibration = this->readAngleRaw_rad();
}

void AMS5048B_Encoder::calibrate(float cal) {
    calibration = cal;
}

uint16_t AMS5048B_Encoder::readAngleRaw_tick() {
    Wire.beginTransmission(address);
    Wire.write(0xFE);
    Wire.endTransmission(false);
    Wire.requestFrom(address,2);

    uint16_t data = Wire.read() << 6;
    data |= Wire.read();
    Wire.endTransmission();

    return data;
}

float AMS5048B_Encoder::readAngleRaw_rad() {
    return this->readAngleRaw_tick() * RAD_PER_TICK;
}
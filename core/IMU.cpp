#include "IMU.h"

int16_t core::IMU::fromByte(Byte lsb, Byte msb)
{
    return ((int16_t)msb << 8 | (int16_t)lsb);
}

MeasureValue& core::IMU::getRaw(MeasureValue& m)
{
    auto x = fromByte(this->acc.readByte(ACC_X_L), this->acc.readByte(ACC_X_H));
    auto y = fromByte(this->acc.readByte(ACC_Y_L), this->acc.readByte(ACC_Y_H));
    auto z = fromByte(this->acc.readByte(ACC_Z_L), this->acc.readByte(ACC_Z_H));
    m.get(0).get(0) = x;
    m.get(0).get(1) = y;
    m.get(0).get(2) = z;

    x = fromByte(this->gyro.readByte(GYRO_X_L), this->gyro.readByte(GYRO_X_H));
    y = fromByte(this->gyro.readByte(GYRO_Y_L), this->gyro.readByte(GYRO_Y_H));
    z = fromByte(this->gyro.readByte(GYRO_Z_L), this->gyro.readByte(GYRO_Z_H));
    m.get(1).get(0) = x;
    m.get(1).get(1) = y;
    m.get(1).get(2) = z;
}

MeasureValue core::IMU::reduce(MeasureValue& m, Vector& factor)
{
    return m >>= factor;
}

Vector core::IMU::toAngle(Vector& raw)
{
    auto normalizedAcc = raw[0];
}

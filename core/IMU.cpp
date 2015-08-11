#include "IMU.h"

int16_t core::IMU::fromByte(Byte lsb, Byte msb)
{
    return ((int16_t)msb << 8 | (int16_t)lsb);
}

MeasureValue& core::IMU::getRaw(MeasureValue& m)
{
    int16_t x = fromByte(this->readByte(0x68, ACC_X_L), this->readByte(0x68, ACC_X_H));
    int16_t y = fromByte(this->readByte(0x68, ACC_Y_L), this->readByte(0x68, ACC_Y_H));
    int16_t z = fromByte(this->readByte(0x68, ACC_Z_L), this->readByte(0x68, ACC_Z_H));
    m[0][0] = x;
    m[0][1] = y;
    m[0][2] = z;

    x = fromByte(this->readByte(0x68, GYRO_X_L), this->readByte(0x68, GYRO_X_H));
    y = fromByte(this->readByte(0x68, GYRO_Y_L), this->readByte(0x68, GYRO_Y_H));
    z = fromByte(this->readByte(0x68, GYRO_Z_L), this->readByte(0x68, GYRO_Z_H));
    m[1][0] = x;
    m[1][1] = y;
    m[1][2] = z;
    return m;
}

MeasureValue core::IMU::reduce(MeasureValue& m, Vector& factor)
{
    return m * factor;
}

// Vector core::IMU::toAngle(MeasureValue raw, Vector angle)
// {
//     float  normalizedFactor = sqrt((raw[0] * raw[0]).foldWithAdd());
//     Vector normalizedAcc    =  raw[0] * (1 / normalizedFactor);
//     // compute the real angle with acc and gyro
//     // Magnet is not support yet.
//     angle[0] = NORMAL_GYR * (angle[0] + raw[1][0] * 0.04)
//              + NORMAL_ACC * atan2(normalizedAcc[1], normalizedAcc[2]) * ARC_PI;
//     angle[1] = NORMAL_GYR * (angle[1] + raw[1][1] * 0.04)
//              + NORMAL_ACC * atan2(normalizedAcc[0], normalizedAcc[2]) * ARC_PI;
//     angle[2] = NORMAL_GYR * (angle[2] + raw[1][2] * 0.04)
//              + NORMAL_ACC * atan2(normalizedAcc[1], normalizedAcc[0]) * ARC_PI;
//     return angle;
// }
Vector core::IMU::toAngle(MeasureValue m, Vector angle)
{
  angle[0] = (angle[0] + m[1][0] * 0.04) * NORMAL_GYR + atan2(m[0][1],m[0][2]) * ARC_PI * NORMAL_ACC;
  angle[1] = (angle[1] + m[1][1] * 0.04) * NORMAL_GYR + atan2(m[0][0],m[0][2]) * ARC_PI * NORMAL_ACC;
  angle[2] =  angle[2] + m[1][2] * 0.04;
  return angle;
}

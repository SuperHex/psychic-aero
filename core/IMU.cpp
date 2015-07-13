#include "IMU.h"

MeasureValue& core::IMU::getMeasure(MeasureValue& m)
{
    auto x = fromMeasure (this->acc.readByte(ACC_X_L), this->acc.readByte(ACC_X_H));
    auto y = fromMeasure (this->acc.readByte(ACC_Y_L), this->acc.readByte(ACC_Y_H));
    auto z = fromMeasure (this->acc.readByte(ACC_Z_L), this->acc.readByte(ACC_Z_H));
    m.get(0).get(0) = x;
    m.get(0).get(1) = y;
    m.get(0).get(2) = z;

    x = fromMeasure (this->gyro.readByte(GYRO_X_L), this->gyro.readByte(GYRO_X_H));
    y = fromMeasure (this->gyro.readByte(GYRO_Y_L), this->gyro.readByte(GYRO_Y_H));
    z = fromMeasure (this->gyro.readByte(GYRO_Z_L), this->gyro.readByte(GYRO_Z_H));
    m.get(1).get(0) = x;
    m.get(1).get(1) = y;
    m.get(1).get(2) = z;
}

Chunk core::IMU::reduce(MeasureValue& m, Factor raw, Factor pitch, Factor yaw)
{
    return (m.get(0) * raw + m.get(1) * pitch + m.get(2) * yaw);
}

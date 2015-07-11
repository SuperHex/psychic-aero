#include "IMU.h"

core::IMU::IMU()
{
    // we should first initialize our sensor
    // set the default value and senesitive.
    // Uncomment to Enable

    // this->acc.writeByte(reg, value);
    // this->gyro.writeByte(reg,value);
}

MeasureValue core::IMU::makeZeroValue()
{
    auto zeros = std::make_tuple (0, 0, 0);
    auto val   = std::make_tuple (zeros, zeros, zeros);
    return val;
}

MeasureValue& core::IMU::getMeasure(MeasureValue& m)
{
    auto x = fromMeasure (this->acc.readByte(ACC_X_L), this->acc.readByte(ACC_X_H));
    auto y = fromMeasure (this->acc.readByte(ACC_Y_L), this->acc.readByte(ACC_Y_H));
    auto z = fromMeasure (this->acc.readByte(ACC_Z_L), this->acc.readByte(ACC_Z_H));
    std::get<0>(std::get<0>(m)) = x;
    std::get<1>(std::get<0>(m)) = y;
    std::get<2>(std::get<0>(m)) = z;

    x = fromMeasure (this->gyro.readByte(GYRO_X_L), this->gyro.readByte(GYRO_X_H));
    y = fromMeasure (this->gyro.readByte(GYRO_Y_L), this->gyro.readByte(GYRO_Y_H));
    z = fromMeasure (this->gyro.readByte(GYRO_Z_L), this->gyro.readByte(GYRO_Z_H));
    std::get<0>(std::get<1>(m)) = x;
    std::get<1>(std::get<1>(m)) = y;
    std::get<2>(std::get<1>(m)) = z;
}

Chunk core::IMU::reduce(const MeasureValue& m, Factor raw, Factor pitch, Factor yaw)
{
    return (std::get<0>(m) * raw + std::get<1>(m) * pitch + std::get<2>(m) * yaw);
}

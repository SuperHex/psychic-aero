
#ifndef __IMU__
#define __IMU__

#include "../base/TWI.h"
#include "../config/Registers.h"
#include "../config/config.h"
#include "../base/container.hpp"
#include <math.h>

namespace core
{
    class IMU
    {
    private:
        base::TWI mpu;

    public:
        IMU() : mpu(MPU6050)
        {
            // unable sleep mode
            mpu.writeByte(PWR_MGMT_1, 0x00);
        }

        // This function using the base/I2C library to communicate with
        // IMU chip, returns 3x3 raw measure value matrix directly.
        // As our measure is a 16-bit value, it will take msb and lsb to int.
        MeasureValue& getRaw(MeasureValue& m);

        // This function will convert two significant byte to a 16-bit int.
        int16_t       fromByte(unsigned char lsb, unsigned char msb);

        // After get raw measure value, next step is do some math to get a
        // three-demension euler angle.
        Vector&       toAngle(MeasureValue& raw, Vector& oldAngle);

        // We can calculate euler angle from both acc and gyro measure.
        // And indeed we should merge this data to a single one since
        // both acc and gyro have measure error.
        // Here is a simple yet useful algorithm called complentary filter:
        // angle = Factor_acc    * angle_from_acc
        //       + Factor_gyro   * angle_from_gyro
        //       + Factor_magnet * angle_from_magnet
        MeasureValue reduce(MeasureValue&, Vector&);
    };
}

#endif

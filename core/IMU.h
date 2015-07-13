
#ifndef __IMU__
#define __IMU__

#include "../base/I2C.h"
#include "../config/Registers.h"
#include "../base/container.hpp"

// Warning:
// we are using an non-standard container library,
// since the stl is not avaliable on avr-gcc platform.

typedef base::container<int16_t> Chunk;
typedef base::container<Chunk>   MeasureValue;
typedef int16_t Factor;

namespace core
{
    class IMU
    {
    private:
        //I2C mpu;
        base::I2C acc;
        base::I2C gyro;

    public:

        // Construct function
        IMU() : acc (ACC_ADD , 0x00)
              , gyro(GYRO_ADD, 0x00)
        {
            // initialize here.
        }

        // Convert a measure value to real value
        // fromMeasure :: Byte -> Byte -> Int
        int16_t fromMeasure(unsigned char lsb, unsigned char msb)
        {
            return ( (int16_t)msb << 8 | (int16_t)lsb );
        }

        MeasureValue& getMeasure(MeasureValue& m);

        Chunk reduce(MeasureValue&, Factor, Factor, Factor);
    };
}

#endif

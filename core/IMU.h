
#ifndef Utopia_IMU_h
#define Utopia_IMU_h

#include "../Base/I2C.h"
#include "../Registers.h"

//#include <tr1/tuple>
using namespace std;

namespace core
{
    typedef std::tuple<int16_t, int16_t, int16_t> Chunk;
    typedef std::tuple<Chunk, Chunk, Chunk> MeasureValue;
    typedef int16_t Factor;

    class IMU
    {
    private:
        //I2C mpu;
        I2C acc  (ACC_ADD , 0x00);
        I2C gryo (GYRO_ADD, 0x00);

    public:

        // Construct function
        IMU();

        // Convert a measure value to real value
        // fromMeasure :: Byte -> Byte -> Int
        int16_t fromMeasure(unsigned char lsb, unsigned char msb)
        {
            return ( (int16_t)msb << 8 | (int16_t)lsb );
        }

        MeasureValue& getMeasure(MeasureValue& m);

        template<typename T1, typename T2, typename T3>
        std::tuple<T1,T2,T3> operator+(const std::tuple<T1,T2,T3>& a, const std::tuple<T1,T2,T3>& b)
        {
            auto c = std::make_tuple(
                std::get<0>(a) + std::get<0>(b)
               ,std::get<1>(a) + std::get<1>(b)
               ,std::get<2>(a) + std::get<2>(b)
            )
            return c;
        }

        Chunk reduce(const MeasureValue&, Factor, Factor, Factor);
    };
}

#endif

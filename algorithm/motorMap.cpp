#include "MotorMap.h"

namespace algorithm
{
    MotorMap::MotorMap(int16_t  mode,
                       int16_t* throttle,
                       base::container<float*> factors)
    {
        this->mode = mode;
        this->throttle = throttle;
        this->factors = factors;
    }

    void MotorMap::setMode(bool mode)
    {
        this->mode = mode;
    }

    void MotorMap::setThrottle(int16_t* thr)
    {
        this->throttle = thr;
    }

    void MotorMap::setFactor(base::container<float*> fact)
    {
        this->factors = fact;
    }

    void MotorMap::run(Vector& pid, int16_t* result)
    {
        if (this->mode == CROSS_MODE)
        {
            result[0] = throttle[0]
                            + this->factors[0][0] * pid[0]
                            + this->factors[1][0] * pid[1]
                            + this->factors[2][0] * pid[2];
            result[1] = throttle[1]
                            + this->factors[0][1] * pid[0]
                            - this->factors[1][1] * pid[1]
                            - this->factors[2][1] * pid[2];
            result[2] = throttle[2]
                            - this->factors[0][2] * pid[0]
                            - this->factors[1][2] * pid[1]
                            + this->factors[2][2] * pid[2];
            result[3] = throttle[3]
                            - this->factors[0][3] * pid[0]
                            + this->factors[1][3] * pid[1]
                            - this->factors[2][3] * pid[2];
            for(int i = 0; i<4; i++)
            {
                if(result[i] > 2500) result[i] = 2500;
                if(result[i] < 0   ) result[i] = 0;
                util::scale(result[i], 0, 2500, 0.25, 0.5);
            }
        }
        if (this->mode == DIRECT_MODE)
        {
            // not implemented yet.
        }
    }
}

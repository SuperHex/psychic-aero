#ifndef __Motor__
#define __Motor__

#include "../algorithm/MotorMap.h"
#include "../algorithm/PID.hpp"
#include "../base/PWM.h"
#include "../base/container.hpp"
#include "../core/IMU.h"
#include "../config/config.h"
#include "../util/util.template.hpp"

namespace core
{
    class Motor : public algorithm::MotorMap,
                  public algorithm::PID< base::container<float> >,
                  public core::IMU,
                  public base::PWM
    {
    public:
        Motor(int16_t* throttle, base::container<float*> mappingFactor)
             : IMU(), PID(), MotorMap(CROSS_MODE, throttle, mappingFactor)
        {

        }
        void holdOn();
        void holdOn(base::container<float> angle);

    protected:
        double res[4];
        MeasureValue measure;
        Vector angle;
    };
}

#endif

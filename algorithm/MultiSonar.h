#ifndef __Multi_Sonar__
#define __Multi_Sonar__

#include "PID.h"
#include "PWM.h"
#include "sonar.h"

namespace algorithm
{
    class MultiSonar : public algorithm::PID<float>,
                       public base::PWM
    {
    private:
        float height[4];
        float setHeight;
        float maxHeight;
        module::sonar s0(PIN_2, PIN_3);
        module::sonar s1(PIN_4, PIN_7);
        module::sonar s2(PIN_8, PIN_10);
        module::sonar s3(PIN_11, PIN_12);

    public:
        MultiSonar(float set) : PID(set, 0.5, 0.2, 0.3), PWM() {}
        bool reachedSetHeight(uint8_t which);
        bool overHeight(uint8_t which);
        void holdOn();
    };
}

#endif

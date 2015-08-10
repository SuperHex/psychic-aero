#ifndef __PWM__
#define __PWM__

#include <avr/io.h>
#include "../config/config.h"
#include "../base/IO.h"

namespace base
{
    class PWM
    {
    public:
        // set duty cycle of our PWM wave
        // Duty_Cycle = (On Time) / (On Time + Off Time) * 100%
        // parameter here should in range [0,1]
        void setDutyCycle(uint8_t, float);
        // set PWM generate mode.
        // Fast PWM Mode by setting to FAST_PWM
        // Phase Corrected Mode by setting to PHASE_CORRECT_PWM
        // under Fast PWM Mode, PWM Frequency is
        //                    clock speed
        // Frequency = ---------------------------
        //             prescaler * (1 + TOP value)
        // and under other mode, it is
        //                    clock speed
        // Frequency = ---------------------------
        //             2 * prescaler * TOP value
        //
        void setMode(uint8_t, uint8_t);
        void setPrescaler(uint8_t);
        void run(uint8_t, float duty_time, uint8_t mode);

    protected:
        bool started;
    };
}

#endif

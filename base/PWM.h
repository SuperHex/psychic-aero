#ifndef __PWM__
#define __PWM__

#include <avr/io.h>
#include "../config/config.h"

namespace base
{
    // Reference website:
    // https://sites.google.com/site/qeewiki/books/avr-guide/pwm-on-the-atmega328
    // http://www.avrfreaks.net/forum/tut-c-newbies-guide-avr-pwm-incomplete?name=PNphpBB2&file=viewtopic&t=68302
    class PWM
    {

    public:
        void enablePin(int16_t);

        // set duty cycle of our PWM wave
        // typically,
        // Duty_Cycle = (On Time) / (On Time + Off Time) * 100%
        // parameter here should between 0 and 1
        void setDutyCycle(float);

        // set PWM generate mode.
        // Fast PWM Mode by setting to 0
        // Phase Corrected Mode by setting to 1
        // Phase and Frequency Corrected Mode by setting to 2
        // under Fast PWM Mode, PWM Frequency is
        //                    clock speed
        // Frequency = ---------------------------
        //             prescaler * (1 + TOP value)
        // and under other mode, it is
        //                    clock speed
        // Frequency = ---------------------------
        //             2 * prescaler * TOP value
        //
        // where TOP value can be set by register OCR0A (max 0xFF)
        void setMode(int16_t);

        // whether enable invert mode
        // not implement.
        void setInvert(bool);

        // set the prescaler factor,
        // It is used to adjust PWM frequency.
        // It should be value of 8, 64, 256, or 1024.
        void setPrescaler(int16_t);

        // you should only use this function to generate PWmM wave.
        void run(int16_t enablePin
                ,int16_t duty_Cycle
                ,int16_t mode
                ,int16_t prescaler
                ,bool    invert
                );
    };
}

#endif

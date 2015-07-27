#ifndef __sonar__
#define __sonar__

#include "../config/config.h"
#include "../base/IO.hpp"
#include <avr/io.h>
#include <util/delay.h>

namespace module
{
    class Sonar
    {
    private:
        uint8_t _trig, _echo;

    public:
        // Binding trig pin and echo pin
        Sonar(uint8_t trig, uint8_t echo);
        // Run measure and get distance in cm
        float run();
    };
}

#endif

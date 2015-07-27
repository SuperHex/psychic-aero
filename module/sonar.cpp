#include "sonar.hpp"

namespace module
{
    using namespace base;

    Sonar::Sonar(uint8_t trig, uint8_t echo)
    {
        pinDirection(trig, OUTPUT);
        pinDirection(echo, INPUT);
        this->_trig = trig;
        this->_echo = echo;
    }

    float Sonar::run()
    {
        pinState(_trig, LOW);
        _delay_us(5);
        pinState(_trig, HIGH);
        _delay_us(20);
        pinState(_trig, LOW);
        uint16_t duration = pulseLength(_echo, HIGH, 6400);
        // Here is the magic happen. It's somehow a math formula
        // map micro second to cm distance.
        return duration / 55.2466;
    }
}

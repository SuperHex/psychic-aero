#include "PWM.h"

namespace base
{
    void PWM::setDutyCycle(uint8_t pin, float duty)
    {
        if(pin == PIN_9 || pin == PIN_10)
            *pinToOCR16(pin) = (uint16_t)(255 * duty);
        else
            *pinToOCR(pin) = (uint8_t)(255 * duty);
    }

    void PWM::setMode(uint8_t pin, uint8_t mode)
    {
        if(pin == PIN_9 || pin == PIN_10)
        {
            switch (mode) {
                case FAST_PWM :
                    *pinToTCCRA(pin) = fastModeTCCRA(pin);
                    TCCR1B |= (1 << WGM12);
                    break;
                case PHASE_CORRECT_PWM :
                    *pinToTCCRA(pin) = phaseModeTCCRA(pin);
                    break;
            }
        }
        else
        {
            switch (mode) {
                case FAST_PWM :
                    *pinToTCCRA(pin) = fastModeTCCRA(pin); // non-invert mode
                    break;
                case PHASE_CORRECT_PWM :
                    *pinToTCCRA(pin) = phaseModeTCCRA(pin); // non-invert mode
                    break;
            }
        }
    }

    void PWM::setPrescaler(uint8_t pin)
    {
        *pinToTCCRB(pin) = MaskTCCRB(pin);
    }

    void PWM::run(uint8_t pin, float duty, uint8_t mode)
    {
        base::pinDirection(pin, OUTPUT);
        this->setPrescaler(pin);
        this->setMode(pin, mode);
        this->setDutyCycle(pin, duty);
    }
}

#include "PWM.h"

void base::PWM::enablePin(int16_t port)
{
    switch (port) {
        case 0 :
            DDRD |= (1 << DDD6); break;
        case 1 :
            DDRD |= (1 << DDD5); break;
        case 2 :
            DDRB |= (1 << DDB1); break;
        case 3 :
            DDRB |= (1 << DDB2); break;
        case 4 :
            DDRB |= (1 << DDB3); break;
        case 5 :
            DDRD |= (1 << DDD3); break;
    }
}

void base::PWM::setDutyCycle(float n)
{
    // max value is 0xFF(255 in decimal)
    // Duty_Cycle is n * 255
    OCR0A = (int16_t)(n * 255);
}

void base::PWM::setInvert(bool enable)
{
    if (enable)
    {
        TCCR0A |= (1 << COM0A1); // set invert true
    }
    else
    {
        TCCR0A &= ~(1 << COM0A1); // set invert false
    }
}

void base::PWM::setMode(int16_t mode)
{
    switch (mode) {
        case 0 : // Fast PWM Mode
            TCCR0A |= (1 << WGM00)
                   |  (1 << WGM01);
            break;
        case 1 : // Phase Corrected Mode
            TCCR0A |= (1 << WGM00);
            break;
        case 2 :
            TCCR0A |= (1 << WGM00);
            break;
    }
}

void base::PWM::setPrescaler(int16_t preScaler)
{
    switch (preScaler) {
        case 8 :
            TCCR0B |= (1 << CS01);
            break;
        case 64 :
            TCCR0B |= (1 << CS00)
                   |  (1 << CS01);
            break;
        case 256 :
            TCCR0B |= (1 << CS02);
            break;
        case 1024 :
            TCCR0B |= (1 << CS00)
                   |  (1 << CS02);
            break;
    }
}

void base::PWM::run(int16_t enablePin
                   ,int16_t duty_Cycle
                   ,int16_t mode
                   ,int16_t prescaler
                   ,bool    invert)
{
    base::PWM::enablePin(enablePin);
    base::PWM::setDutyCycle(duty_Cycle);
    base::PWM::setMode(mode);
    base::PWM::setInvert(invert);
    base::PWM::setPrescaler(prescaler);
}

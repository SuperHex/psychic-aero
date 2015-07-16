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

void base::PWM::setDutyCycle(int16_t pin, float n)
{
    // max value is 0xFF(255 in decimal)
    // Duty_Cycle is n * 255
    switch (pin) {
        case 0 :
            OCR0A = (int16_t)(n * 255);
            break;
        case 1 :
            OCR0B = (int16_t)(n * 255);
            break;
        case 2 :
            OCR1A = (int16_t)(n * 255);
            break;
        case 3 :
            OCR1B = (int16_t)(n * 255);
            break;
        case 4 :
            OCR2A = (int16_t)(n * 255);
            break;
        case 5 :
            OCR2B = (int16_t)(n * 255);
            break;
    }

}

void base::PWM::setInvert(int16_t pin, bool enable)
{
    int16_t p;
    switch (pin) {
        case 0 :
        case 1 :
            p = TCCR0A; break;
        case 2 :
        case 3 :
            p = TCCR1A; break;
        case 4 :
        case 5 :
            p = TCCR2A; break;
    }

    if (enable)
    {
        p |= (1 << COM0A1); // set invert true
    }
    else
    {
        p ^= (1 << COM0A1); // set invert false
    }
}

void base::PWM::setMode(int16_t pin, int16_t mode)
{
    int16_t p;
    switch (pin) {
        case 0 :
        case 1 :
            p = TCCR0A; break;
        case 2 :
        case 3 :
            p = TCCR1A; break;
        case 4 :
        case 5 :
            p = TCCR2A; break;
    }

    switch (mode) {
        case 0 : // Fast PWM Mode
            p |= (1 << WGM00)
              |  (1 << WGM01);
            break;
        case 1 : // Phase Corrected Mode
            p |= (1 << WGM00);
            break;
        case 2 :
            p |= (1 << WGM00);
            break;
    }
}

void base::PWM::setPrescaler(int16_t pin, int16_t preScaler)
{
    int16_t p;
    switch (pin) {
        case 0 :
        case 1 :
            p = TCCR0B; break;
        case 2 :
        case 3 :
            p = TCCR1B; break;
        case 4 :
        case 5 :
            p = TCCR2B; break;
    }

    switch (preScaler) {
        case 8 :
            p |= (1 << CS01);
            break;
        case 64 :
            p |= (1 << CS00)
              |  (1 << CS01);
            break;
        case 256 :
            p |= (1 << CS02);
            break;
        case 1024 :
            p |= (1 << CS00)
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
    base::PWM::setDutyCycle(enablePin, duty_Cycle);
    base::PWM::setMode(enablePin, mode);
    base::PWM::setInvert(enablePin, invert);
    base::PWM::setPrescaler(enablePin, prescaler);
}

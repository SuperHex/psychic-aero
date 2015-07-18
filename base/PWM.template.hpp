#ifndef __PWM__
#define __PWM__

#include <avr/io.h>
#include "../config/config.h"

namespace base
{
    template<size_t N>
    class PWM
    {
    public:
        // set duty cycle of our PWM wave
        // Duty_Cycle = (On Time) / (On Time + Off Time) * 100%
        // parameter here should in range [0,1]
        void setDutyCycle(float);
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
        void setMode(size_t);
        void setPrescaler(size_t);
        void run(float duty_time, size_t mode, size_t prescale);
    };

    template<>
    void PWM<PWM_PIN3>::setDutyCycle(float n)
    {
        OCR0A = (uint16_t)(255 * n);
    }

    template<>
    void PWM<PWM_PIN5>::setDutyCycle(float n)
    {
        OCR0B = (uint16_t)(255 * n);
    }

    template<>
    void PWM<PWM_PIN6>::setDutyCycle(float n)
    {
        OCR1A = (uint16_t)(255 * n);
    }

    template<>
    void PWM<PWM_PIN9>::setDutyCycle(float n)
    {
        OCR1B = (uint16_t)(255 * n);
    }

    template<>
    void PWM<PWM_PIN10>::setDutyCycle(float n)
    {
        OCR2A = (uint16_t)(255 * n);
    }

    template<>
    void PWM<PWM_PIN11>::setDutyCycle(float n)
    {
        OCR2B = (uint16_t)(255 * n);
    }

    template<>
    void PWM<PWM_PIN3>::setMode(size_t mode)
    {
        switch (mode) {
            case FAST_PWM :
                TCCR0A = (1 << WGM00)  |  (1 <<WGM01)   // fast pwm mode
                       | (1 << COM0A1) |  (1 <<COM0B1); // non-invert mode
                break;
            case PHASE_CORRECT_PWM :
                TCCR0A = (1 << WGM00)                   // phase corrected mode
                       | (1 << COM0A1) | (1 << COM0B1); // non-invert mode
        }
    }

    template<>
    void PWM<PWM_PIN5>::setMode(size_t mode)
    {
        switch (mode) {
            case FAST_PWM :
                TCCR0A = (1 << WGM00)  |  (1 <<WGM01)   // fast pwm mode
                       | (1 << COM0A1) |  (1 <<COM0B1); // non-invert mode
                break;
            case PHASE_CORRECT_PWM :
                TCCR0A = (1 << WGM00)                   // phase corrected mode
                       | (1 << COM0A1) | (1 << COM0B1); // non-invert mode
        }
    }

    // Pin6 and Pin9 can provid up to 10-bit resolution, which is difference
    // with other two 8-bit timer. We only need 8-bit resolution here.
    // To use 10-bit resolution, change following registers:
    // TCCR1A |= (1 << WGM11) | (1 << WGM10); // 10-bit Phase Correct PWM
    // TCCR1A |= (1 << COM1A1)| (1 << COM1B1);
    // -------------------------------------
    // TCCR1A |= (1 << WGM11) | (1 << WGM10); // 10-bit Fast PWM
    // TCCR1A |= (1 << COM1A1)| (1 <<COM1B1);
    // TCCR1B |= (1 << WGM12);
    template<>
    void PWM<PWM_PIN6>::setMode(size_t mode)
    {
        switch (mode) {
            case FAST_PWM :
                TCCR1A = (1 << WGM10)                   // fast pwm mode
                       | (1 << COM1A1) |  (1 <<COM1B1); // non-invert mode
                TCCR1B |=(1 << WGM12);
                break;
            case PHASE_CORRECT_PWM :
                TCCR1A = (1 << WGM10)                   // phase corrected mode
                       | (1 << COM1A1) | (1 << COM1B1); // non-invert mode
        }
    }

    template<>
    void PWM<PWM_PIN9>::setMode(size_t mode)
    {
        switch (mode) {
            case FAST_PWM :
                TCCR1A = (1 << WGM10)                   // fast pwm mode
                       | (1 << COM1A1) |  (1 <<COM1B1); // non-invert mode
                TCCR1B |=(1 << WGM12);
                break;
            case PHASE_CORRECT_PWM :
                TCCR1A = (1 << WGM10)                   // phase corrected mode
                       | (1 << COM1A1) | (1 << COM1B1); // non-invert mode
        }
    }

    template<>
    void PWM<PWM_PIN10>::setMode(size_t mode)
    {
        switch (mode) {
            case FAST_PWM :
                TCCR0A = (1 << WGM20)  |  (1 <<WGM21)   // fast pwm mode
                       | (1 << COM2A1) |  (1 <<COM2B1); // non-invert mode
                break;
            case PHASE_CORRECT_PWM :
                TCCR0A = (1 << WGM20)                   // phase corrected mode
                       | (1 << COM2A1) | (1 << COM2B1); // non-invert mode
        }
    }

    template<>
    void PWM<PWM_PIN11>::setMode(size_t mode)
    {
        switch (mode) {
            case FAST_PWM :
                TCCR0A = (1 << WGM20)  |  (1 <<WGM21)   // fast pwm mode
                       | (1 << COM2A1) |  (1 <<COM2B1); // non-invert mode
                break;
            case PHASE_CORRECT_PWM :
                TCCR0A = (1 << WGM20)                   // phase corrected mode
                       | (1 << COM2A1) | (1 << COM2B1); // non-invert mode
        }
    }

    template<>
    void PWM<PWM_PIN3>::setPrescaler(size_t p)
    {
        switch (p) {
            case 0 :
                TCCR0B |= (1 << CS00); // no prescaling
            case 8 :
                TCCR0B |= (1 << CS01); // prescaling 8
        }
    }

    template<>
    void PWM<PWM_PIN5>::setPrescaler(size_t p)
    {
        switch (p) {
            case 0 :
                TCCR0B |= (1 << CS00); // no prescaling
            case 8 :
                TCCR0B |= (1 << CS01); // prescaling 8
        }
    }

    template<>
    void PWM<PWM_PIN6>::setPrescaler(size_t p)
    {
        switch (p) {
            case 0 :
                TCCR0B |= (1 << CS10); // no prescaling
            case 8 :
                TCCR0B |= (1 << CS11); // prescaling 8
        }
    }

    template<>
    void PWM<PWM_PIN9>::setPrescaler(size_t p)
    {
        switch (p) {
            case 0 :
                TCCR0B |= (1 << CS10); // no prescaling
            case 8 :
                TCCR0B |= (1 << CS11); // prescaling 8
        }
    }

    template<>
    void PWM<PWM_PIN10>::setPrescaler(size_t p)
    {
        switch (p) {
            case 0 :
                TCCR0B |= (1 << CS20); // no prescaling
            case 8 :
                TCCR0B |= (1 << CS21); // prescaling 8
        }
    }

    template<>
    void PWM<PWM_PIN11>::setPrescaler(size_t p)
    {
        switch (p) {
            case 0 :
                TCCR0B |= (1 << CS20); // no prescaling
            case 8 :
                TCCR0B |= (1 << CS21); // prescaling 8
        }
    }

    template<size_t N>
    void PWM<N>::run(float duty, size_t mode, size_t p)
    {
        this->setMode(mode);
        this->setPrescaler(p);
        this->setDutyCycle(duty);
    }
}
#endif

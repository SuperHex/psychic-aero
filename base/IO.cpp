#include "IO.hpp"

namespace base
{
    uint16_t calculatePrescaler()
    {
        Byte status = TCCR1B;
        status &= (1 << CS12) | (1 << CS11) | (1 << CS10);
        switch (status) {
            case 0 :
                return 0;
            case 1 :
                return 1;
            case 2 :
                return 8;
            case 3 :
                return 64;
            case 4 :
                return 256;
            case 5 :
                return 1024;
        }
    }


    Byte pinToMask(uint8_t pin)
    {
        switch (pin) {
            case PIN_2 :
                return (1 << PD2);
            case PIN_3 :
                return (1 << PD3);
            case PIN_4 :
                return (1 << PD4);
            case PIN_5 :
                return (1 << PD5);
            case PIN_6 :
                return (1 << PD6);
            case PIN_7 :
                return (1 << PD7);
            case PIN_8 :
                return (1 << PB0);
            case PIN_9 :
                return (1 << PB1);
            case PIN_10 :
                return (1 << PB2);
            case PIN_11 :
                return (1 << PB3);
            case PIN_12 :
                return (1 << PB4);
            case PIN_13 :
                return (1 << PB5);
            case PIN_A0 :
                return (1 << PC0);
            case PIN_A1 :
                return (1 << PC1);
            case PIN_A2 :
                return (1 << PC2);
            case PIN_A3 :
                return (1 << PC3);
            case PIN_A4 :
                return (1 << PC4);
            case PIN_A5 :
                return (1 << PC5);
        }
    }

    Byte* pinToPort(uint8_t pin)
    {
        Byte* reg;
        if (pin >= PIN_2 && pin <= PIN_7)        *reg = PORTD;
        else if (pin >= PIN_12 && pin <= PIN_13) *reg = PINB;
        else if (pin >= PIN_A0 && pin <= PIN_A5) *reg = PINC;
        return reg;
    }

    Byte* pinToDDR(uint8_t pin)
    {
        Byte* reg;
        if (pin >= PIN_2 && pin <= PIN_7)        *reg = DDRD;
        else if (pin >= PIN_12 && pin <= PIN_13) *reg = DDRB;
        else if (pin >= PIN_A0 && pin <= PIN_A5) *reg = DDRC;
        return reg;
    }

    Byte* inputRegister(uint8_t pin)
    {
        Byte* reg;
        if (pin >= PIN_2 && pin <= PIN_7)        *reg = PIND;
        else if (pin >= PIN_12 && pin <= PIN_13) *reg = PINB;
        else if (pin >= PIN_A0 && pin <= PIN_A5) *reg = PINC;
        return reg;
    }

    uint32_t pulseLength(uint8_t pin, bool state, uint32_t timeout)
    {
        uint32_t duration;
        Byte pinMask = pinToMask(pin);
        Byte stateMask = state ? pinMask : 0;
        uint32_t retry = 0;
        // wait for previous signal stop
        while(*inputRegister(pin) & pinMask == stateMask)
            if(retry++ == timeout) return 0;
        // wait for assigned signal start
        while(*inputRegister(pin) & pinMask != stateMask)
            if(retry++ == timeout) return 0;
        // real count start
        while(*inputRegister(pin) & pinMask == stateMask)
        {
            if(retry++ == timeout) return 0;
            duration++;
        }
        // These two magic number is used to get correct clock cycle,
        // since one loop step will cost more than one cycle.
        // "It multiplies that by the number of clock cycle each time
        // through the loop takes (21 or 24 depending on the compiler version).
        // It adds the amount of fixed overhead cycles (16) to get
        // total clock cycles during the pulse. "
        return (duration * 21 + 16) / 16;
    }

    void pinDirection(uint8_t pin, bool mode)
    {
        mode ? (*pinToDDR(pin) |= pinToMask(pin))
             : (*pinToDDR(pin) &= ~(pinToMask(pin)));
    }

    void pinState(uint8_t pin, bool state)
    {
        state ? (*pinToPort(pin) |= pinToMask(pin))
              : (*pinToPort(pin) &= ~(pinToMask(pin)));
    }
}

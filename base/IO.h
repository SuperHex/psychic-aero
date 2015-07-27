#ifndef __IO__
#define __IO__

#include <avr/io.h>
#include <avr/interrupt.h>
#include "../config/config.h"

 namespace base
 {
     uint16_t calculatePrescaler();
     Byte     pinToMask(uint8_t pin);
     volatile Byte*    pinToPort(uint8_t pin);
     volatile Byte*    pinToDDR(uint8_t pin);
     volatile Byte*    inputRegister(uint8_t pin);

     // Measure pulse length on given pin.
     // It will return a time in microseconds(us).
     uint32_t pulseLength(uint8_t pin, bool state, uint32_t timeout);

     // Set a pin as input or output.
     // Can be used as pinMode(PIN_3, OUTPUT)
     void     pinDirection(uint8_t pin, bool mode);

     // Used to set high or low to a pin.
     // Can be used as pinState(PIN_3, HIGH)
     void     pinState(uint8_t pin, bool state);
 }

#endif

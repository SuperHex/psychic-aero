#ifndef __IO__
#define __IO__

#include <avr/io.h>
#include <avr/interrupt.h>
#include "../config/config.h"

 namespace base
 {
     uint16_t calculatePrescaler();
     Byte     pinToMask(uint8_t pin);
     volatile Byte*   pinToPort(uint8_t pin);
     volatile Byte*   pinToDDR(uint8_t pin);
     volatile Byte*   inputRegister(uint8_t pin);
     volatile Byte*   pinToTCCRA(uint8_t pin);
     uint8_t fastModeTCCRA(uint8_t pin);
     uint8_t phaseModeTCCRA(uint8_t pin);
     volatile Byte*   pinToTCCRB(uint8_t pin);

     /*
      * We should update our prescaler here.
      * CSx2   CSx1   CSx0    Prescaler
      * ---- | ---- | ---- | ----------
      *  0   |  1   |  0   |  clk / 8
      *  0   |  1   |  1   |  clk / 64
      *  1   |  0   |  0   |  clk / 256
      *  1   |  0   |  1   |  clk / 1024
      * Here we use clk / (256 * 256) = 244Hz PWM wave.
      * (Mode = Fast PWM, Prescaler = 256)
      */
     uint8_t MaskTCCRB(uint8_t pin);
     volatile uint8_t*  pinToOCR(uint8_t pin);
     volatile uint16_t* pinToOCR16(uint8_t pin);
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

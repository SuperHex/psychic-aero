#ifndef __ICU__
#define __ICU__

#include <avr/io.h>
#include <avr/interrupt.h>
#include "../config/config.h"

 namespace base
 {
     volatile uint16_t base::calculatePrescaler();
     Byte base::pinToMask(uint16_t pin);
     Byte* base::inputRegister(uint16_t pin);
     uint32_t base::pulseLength(uint16_t pin, bool state, uint32_t timeout);
 }

#endif

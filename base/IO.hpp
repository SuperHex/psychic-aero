#ifndef __ICU__
#define __ICU__

#include <avr/io.h>
#include <avr/interrupt.h>
#include "../config/config.h"

 namespace base
 {
     uint16_t calculatePrescaler();
     Byte pinToMask(uint16_t);
     Byte* inputRegister(uint16_t);
     uint32_t pulseLength(uint16_t, bool, uint32_t);
 }

#endif

#ifndef __USART__
#define __USART__

#include <avr/io.h>
#include "../config/config.h"

namespace base
{
    class USART
    {
        void init(const uint32_t baud);
        void transmit(const unsigned char data);
        unsigned char receive();
    };
}

#endif

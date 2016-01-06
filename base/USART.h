#ifndef __USART__
#define __USART__

#include <avr/io.h>
#include "../config/config.h"

namespace base
{
    class USART
    {
    public:
        static void init(const uint32_t baud);
        static void transmit(const unsigned char data);
        static unsigned char receive();
    private:
        USART();
    };
}

#endif

#ifndef __USART__
#define __USART__

#include <avr/io.h>

namespace base
{
    class USART
    {
        void begin(uint32_t baud);

    };
}

#endif

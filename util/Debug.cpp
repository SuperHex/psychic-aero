#include "Debug.h"

namespace util
{
    void Debug::Dump(unsigned char data)
    {
        USART::transmit(data);
    }
}

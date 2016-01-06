#ifndef __DEBUG_UTIL__
#define __DEBUG_UTIL__

#include "../base/USART.h"
using namespace base;

namespace util
{
    class Debug
    {
    public:
        // Note: USART initialization is required.
        static void Dump(unsigned char);
        Debug()
        {
            USART::init(9600);
        }
    };
}


#endif

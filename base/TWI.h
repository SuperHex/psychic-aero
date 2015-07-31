#ifndef __TWI__
#define __TWI__

#include "../base/IO.h"
#include <compat/twi.h>

namespace base
{
    class TWI
    {
    private:
        inline void ERROR() { this->TWIStop(); }
        void    TWIStart();
        void    TWIStop();
        void    TWIWrite(uint8_t data);
        uint8_t readACK();
        uint8_t readNACK();
        uint8_t status();
    public:
        // Before start any communication, you should always
        // invoke init() first to join I2C bus.
        void    init();
        void    writeByte(uint8_t addr, uint8_t reg, uint8_t data);
        uint8_t readByte(uint8_t addr, uint8_t reg);
        uint8_t readMultiByte(uint8_t addr, uint8_t reg,
                               uint8_t* buffer, uint8_t len);
    };
}
#endif

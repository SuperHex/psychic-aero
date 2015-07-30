#include "AnotherI2C.h"

namespace base
{
    void AnotherI2C::init()
    {
        TWSR = 0x00;
        TWBR = 0x4B;
        TWCR = (1 << TWEN);
    }

    void AnotherI2C::TWIStart()
    {
        TWCR = (1 << TWINT)
             | (1 << TWSTA)
             | (1 << TWEN);
        while ((TWCR & (1 << TWINT)) == 0);
    }

    void AnotherI2C::TWIStop()
    {
        TWCR = (1 << TWINT)
             | (1 << TWSTO)
             | (1 << TWEN);
    }

    void AnotherI2C::TWIWrite(uint8_t data)
    {
        TWDR = data;
        TWCR = (1 << TWINT)
             | (1 << TWEN);
        while ((TWCR & (1 << TWINT)) == 0);
    }

    uint8_t AnotherI2C::readACK()
    {
        TWCR = (1 << TWINT)
             | (1 << TWEN)
             | (1 << TWEA);
        while ((TWCR & (1 << TWINT)) == 0);
        return TWDR;
    }

    uint8_t AnotherI2C::readNACK()
    {
        TWCR = (1 << TWINT)
             | (1 << TWEN);
        while ((TWCR & (1 <<TWINT)) == 0);
        return TWDR;
    }

    uint8_t getStatus()
    {
        return (TWSR & 0xF8);
    }

    
}

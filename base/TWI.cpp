#include "TWI.h"

namespace base
{
    void TWI::init()
    {
        base::pinState(PIN_A4, HIGH);
        base::pinState(PIN_A5, HIGH);
        TWSR = 0x00;
        TWBR = 0x4B;
        TWCR = (1 << TWEN);
    }

    void TWI::TWIStart()
    {
        TWCR = (1 << TWINT)
             | (1 << TWSTA)
             | (1 << TWEN);
        while ((TWCR & (1 << TWINT)) == 0);
    }

    void TWI::TWIStop()
    {
        TWCR = (1 << TWINT)
             | (1 << TWSTO)
             | (1 << TWEN);
    }

    void TWI::TWIWrite(uint8_t data)
    {
        TWDR = data;
        TWCR = (1 << TWINT)
             | (1 << TWEN);
        while ((TWCR & (1 << TWINT)) == 0);
    }

    uint8_t TWI::readACK()
    {
        TWCR = (1 << TWINT)
             | (1 << TWEN)
             | (1 << TWEA);
        while ((TWCR & (1 << TWINT)) == 0);
        return TWDR;
    }

    uint8_t TWI::readNACK()
    {
        TWCR = (1 << TWINT)
             | (1 << TWEN);
        while ((TWCR & (1 <<TWINT)) == 0);
        return TWDR;
    }

    uint8_t TWI::status()
    {
        return (TWSR & 0xF8);
    }

    void TWI::writeByte(uint8_t addr, uint8_t reg, uint8_t data)
    {
        uint8_t SLA_W = (addr << 1);

        this->TWIStart();
        this->TWIWrite(SLA_W);
        this->TWIWrite(reg);
        this->TWIWrite(data);
        this->TWIStop();
    }

    uint8_t TWI::readByte(uint8_t addr, uint8_t reg)
    {
        uint8_t SLA_W = ( addr << 1);
        uint8_t SLA_R = ((addr << 1) | 1);
        uint8_t buffer;

        this-> TWIStart();
        this->TWIWrite(SLA_W);
        this->TWIWrite(reg);
        this->TWIStart();
        this->TWIWrite(SLA_R);
        buffer = this->readNACK();
        this->TWIStop();
        return buffer;
    }

    uint8_t TWI::readMultiByte(uint8_t addr, uint8_t reg,
                                       uint8_t* buffer, uint8_t len)
   {
       uint8_t SLA_W = ( addr << 1);
       uint8_t SLA_R = ((addr << 1) | 1);
       uint8_t buff[len];

       this->TWIStart();
       this->TWIWrite(SLA_W);
       this->TWIWrite(reg);
       this->TWIStart();
       this->TWIWrite(SLA_R);

       for(uint8_t i=0; i<(len-1); i++)
       {
           buff[i] = this->readACK();
       }
       buff[len-1] = this->readNACK();
       *buffer = *buff;
       return 1;
   }

}


#ifndef __I2C__
#define __I2C__

#include "../config/config.h"
#include <avr/io.h>
#include <util/delay.h>
#include <compat/twi.h>

#define MAX_RETRY 10

// The 7 bits address consist of 4 bits device id and 3 bits physical address.
// Such as:
//      1 0 1 0           0 0 0
//    Identifiter | Physical Address
// If we have other same chip connected to I2c bus, it will be
//      1 0 1 0           0 0 1
//    Identifiter | Physical Address
// and so on...
#define EEPROM_ID   0xA0
#define EEPROM_ADDR 0x00

#define I2C_START 0
#define I2C_DATA  1
#define I2C_STOP  2


namespace base
{
    class I2C
    {
    private:
        unsigned char deviceAddress;
        unsigned char status;

    public:
        I2C(unsigned char addr);
        I2C(unsigned char id, unsigned char addr);
        int writeByte(uint16_t reg, char data);
        unsigned char readByte(uint16_t addr);
        unsigned char transmit(unsigned int type);

        inline int quit()
        {
            transmit(I2C_STOP);
            return -1;
        }
    };
}



#endif

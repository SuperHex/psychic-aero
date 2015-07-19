#ifndef __SPI__
#define __SPI__

#include <avr/io.h>
#include "../config/config.h"

namespace base
{
    class SPI
    {
        template<size_t Mode>
        void inline init();
        void transmit(Byte& data);
        Byte receive();
    };

    template<>
    void inline SPI::init<MASTER_MODE>()
    {
        DDRB |= (1 << PB3)   // set MOSI as output
             |  (1 << PB5)   // set SCK  as output
             |  (1 << PB2);  // set SS'  as output since we have only one slave
        SPCR  = (1 << SPE)   // enable SPI
              | (1 << MSTR)  // set SPI as master
              | (1 << SPR0); // set clock as F_CPU / 16
    }

    template<>
    void inline SPI::init<SLAVE_MODE>()
    {
        DDRB |= (1 << PB4);  // set MISO as output, all other as input
        SPCR  = (1 << SPE);  // enable SPI
    }

    void SPI::transmit(Byte& data)
    {
        // To start a SPI transmission, simply feed data into SPI Data Register
        SPDR = data;
        // Wait until transmission complete
        while (!(SPSR & (1 << SPIF)));
    }

    Byte SPI::receive()
    {
        // Wait until receive complete
        while (!(SPSR & (1 << SPIF)));
        return SPDR;
    }
}
#endif

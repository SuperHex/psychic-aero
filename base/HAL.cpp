/* Hardware Abstract Layer */

#ifndef __HAL__
#define __HAL__
/*
#include ../config/config.h
#include <avr/io.h>
*/
namespace base
{
    template< class init_traits, class rw_traits >
    struct hal
    {
        typedef init_traits I;
        typedef rw_traits   RW;
    public:
        hal(){ I::init(); }
        virtual ~hal();
        virtual void write(const unsigned char data)
        {
            RW::write(data);
        }
        virtual unsigned char read ()
        {
            return RW::read();
        }
    };

    struct skip_init{ static void init() {} };

    struct USART_default_init
    {
        static void init(const long baudRate)
        {/*
            long ubrr = F_CPU / 16 / baudRate - 1;

            // Set baud rate
            UBRR0H = ubrr >> 8;
            UBRR0L = ubrr;

            // Enable receiver and transmitter
            UCSR0B = (1 << RXEN0) | (1 << TXEN0);

            // Set frame format: 8 data, 1 stop bit, no parity check.
            // For a custom setting, please refer Atmel Datasheet page 195
            UCSR0C = (3 << UCSZ00);*/
        }
    };

    struct USART_8N1_RW
    {
    public:
        static void write(const unsigned char data)
        {/*
            // Wait until buffer empty
            while (!(UCSR0A & (1 << UDRE0)));
            // load and send
            UDR0 = data;*/
        }

        static unsigned char read()
        {/*
            // Wait until buffer empty
            while (!(UCSR0A & (1 << RXC0)));
            return UDR0;*/
        }
    };

    struct SPI_RW
    {
        static void write(unsigned char data)
        {/*
            // To start a SPI transmission, simply feed data into SPI Data Register
            SPDR = data;
            // Wait until transmission complete
            while (!(SPSR & (1 << SPIF)));*/
        }

        static unsigned char read()
        {/*
            // Wait until receive complete
            while (!(SPSR & (1 << SPIF)));
            return SPDR;*/
        }
    };

    struct SPI_master_init
    {
        static void init()
        {/*
            DDRB |= (1 << PB3)   // set MOSI as output
                 |  (1 << PB5)   // set SCK  as output
                 |  (1 << PB2);  // set SS'  as output since we have only one slave
            SPCR  = (1 << SPE)   // enable SPI
                 |  (1 << MSTR)  // set SPI as master
                 |  (1 << SPR0); // set clock as F_CPU / 16*/
        }
    };

    struct SPI_slave_init
    {
        static void init()
        {/*
            DDRB |= (1 << PB4);  // set MISO as output, all other as input
            SPCR  = (1 << SPE);  // enable SPI*/
        }
    };

    template< class T = USART_default_init >
    struct USART : public hal< skip_init, USART_8N1_RW >
    {
    public:
        USART(const long Rate){ T::init(Rate); }
        virtual ~USART();
    };
    typedef USART< > Serial;

    template< class T >
    struct SPI : public hal< T, SPI_RW > {};
    typedef SPI< SPI_master_init > SPIMaster;
    typedef SPI< SPI_slave_init >  SPISlave;

}

#endif

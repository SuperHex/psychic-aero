/* Hardware Abstract Layer */

#ifndef __HAL__
#define __HAL__

//#include ../config/config.h
//#include <avr/io.h>

namespace base
{
    template< typename In  = unsigned char,
              typename Out = unsigned char >
    struct hal
    {
    public:
        typedef Out Type;
        hal();
        virtual ~hal();

        virtual void write(const In params) = 0;
        virtual Type read () = 0;
    };

    struct USART_8N1
    {
    public:
        static void initialSetup(const long baudRate)
        {
            long ubrr = F_CPU / 16 / baudRate - 1;

            // Set baud rate
            UBRR0H = ubrr >> 8;
            UBRR0L = ubrr;

            // Enable receiver and transmitter
            UCSR0B = (1 << RXEN0) | (1 << TXEN0);

            // TODO: make it no stop bit, 1 odd check
            // Set frame format: 8 data, 2 stop bit
            // For a custom setting, please refer Atmel Datasheet page 195
            UCSR0C = (1 << USBS0) | (3 << UCSZ00);
        }

        static void transmit(const unsigned char data)
        {
            // Wait until buffer empty
            while (!(UCSR0A & (1 << UDRE0)));
            // load and send
            UDR0 = data;
        }

        static unsigned char receive()
        {
            // Wait until buffer empty
            while (!(UCSR0A & (1 << RXC0)));
            return UDR0;
        }
    };

    template< class hardware_traits = USART_8N1 >
    struct USART : hal< >
    {
        typedef hardware_traits H;
    public:
        USART(const long Rate)
        {
            H::initialSetup(Rate);
        }
        virtual ~USART();

        void write(const unsigned char data)
        {
            H::transmit(data);
        }

        Type read()
        {
            return H::receive();
        }

    };
}

#endif

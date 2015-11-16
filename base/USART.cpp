#include "USART.h"

namespace base
{
    void USART::init(const uint32_t baud)
    {
        uint16_t ubrr = F_CPU / 16 / baud - 1;

        // Set baud rate
        UBRR0H = ubrr >> 8;
        UBRR0L = ubrr;

        // Enable receiver and transmitter
        UCSR0B = (1 << RXEN0) | (1 << TXEN0);

        // Set frame format: 8 data, 2 stop bit
        // For a custom setting, please refer Atmel Datasheet page 195
        UCSR0C = (1 << USBS0) | (3 << UCSZ00);
    }

    void USART::transmit(const unsigned char data)
    {
        // Wait until buffer empty
        while (!(UCSR0A & (1 << UDRE0)));

        // load and send
        UDR0 = data;
    }

    unsigned char USART::receive()
    {
        // Wait until buffer empty
        while (!(UCSR0A & (1 << RXC0)));
        return UDR0;
    }
}

#include "USART.h"

namespace base
{
    void USART::begin(uint32_t baud)
    {
        Byte ubrr = F_CPU / 16 / baud - 1;

        // Set baud rate
        UBRR0H = ubrr >> 8;
        UBRR0L = ubrr;

        // Enable receiver and transmitter
        UCSR0B = (1 << RXEN0) | (1 << TXEN0);

        // Set frame format: 8 data, 2 stop bit
        UCSR0C = (1 << USBS0) | (3 << UCSZ00);
    }
}

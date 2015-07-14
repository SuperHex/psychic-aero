#include "I2C.h"

namespace base
{

    base::I2C::I2C(unsigned char id, unsigned char addr)
    {
        // The SCL frequency can be calculated by this formular:
        //
        //                        CPU Frequency
        // SCL frequency = ---------------------------
        //                  16 + 2(TWBR) * (Prescaler)
        //
        // where the TWBR is TWI Bit Rate Register,
        // and Prescaler(can be selected in TWSR) equal to 1 here.
        TWSR = 0x00;
        TWBR = 0x30;

        //   0 0 0 0         0 0 0             0
        // identifiter | physical addr | write/reada mode
        this -> deviceAddress = (id & 0xF0) | ((addr & 0x07) << 1);
    }

    base::I2C::I2C(unsigned char addr)
    {
        TWSR = 0x00;
        TWBR = 0x30;
        this -> deviceAddress = addr;
    }


    unsigned char base::I2C::transmit(unsigned int type)
    {
        switch (type)
        {
            case I2C_START:
                TWCR = (1 << TWINT) // TWI Interrupt flag
                     | (1 << TWSTA) // TWI Start Condition Bit
                     | (1 << TWEN); // TWI Enable Bit
                break;
            case I2C_DATA:
                TWCR = (1 << TWINT)
                     | (1 << TWEN );
                break;
            case I2C_STOP:
                TWCR = (1 << TWINT)
                     | (1 << TWEN )
                     | (1 << TWSTO);
                break;
        }

        // wait until TWINT to '1'
        while( ! (TWCR & (1 << TWINT) ));
        return (TWSR & 0xF8);
    }


    int base::I2C::writeByte(uint16_t reg, char data)
    {
        unsigned char retryCount = 0;

        retry:
            if (retryCount++ > MAX_RETRY) return -1;

            // Start transmission
            this -> status = transmit(I2C_START);
            // if message lost, then retry; if not start, then give up.
            if (this -> status == TW_MT_ARB_LOST) goto retry;
            if ((this -> status != TW_START) && (this -> status != TW_REP_START)) quit();

            // send slave address we want to communicate
            // by writing to data register.
            TWDR = this -> deviceAddress | TW_WRITE;
            // Flush the address
            this -> status = transmit(I2C_DATA);
            // if there is no reply, retry.
            if ((this -> status != TW_MT_SLA_NACK) || (this -> status == TW_MT_ARB_LOST))
               goto retry;
            if (this -> status != TW_MT_SLA_ACK) quit();

            // start send the register address we want to write
            // first send the high 8 bits
            TWDR = reg >> 8;
            this -> status = transmit(I2C_DATA);
            if (this -> status != TW_MT_DATA_ACK) quit();

            // and the low 8 bits
            TWDR = reg;
            this -> status = transmit(I2C_DATA);
            if (this -> status != TW_MT_DATA_ACK) quit();

            // Finally send the data
            TWDR = data;
            this -> status = transmit(I2C_DATA);
            if (this -> status != TW_MT_DATA_ACK) quit();
            return 1;
    }

    unsigned char base::I2C::readByte(uint16_t reg)
    {
        unsigned char retryCount = 0;

        retry:
            if (retryCount++ > MAX_RETRY) return -1;

            this -> status = transmit(I2C_START);
            if (this -> status == TW_MT_ARB_LOST) goto retry;
            if ((this -> status != TW_START) && (this -> status != TW_REP_START)) quit();

            // send slave address we want to communicate
            // by writing to data register.
            TWDR = this -> deviceAddress | TW_WRITE;
            // Flush the address
            this -> status = transmit(I2C_DATA);
            // if there is no reply, retry.
            if ((this -> status != TW_MT_SLA_NACK) ||
               (this -> status == TW_MT_ARB_LOST))
               goto retry;
            if (this -> status != TW_MT_SLA_ACK) quit();

            // start send the register address we want to write
            // first send the high 8 bits
            TWDR = reg >> 8;
            this -> status = transmit(I2C_DATA);
            if (this -> status != TW_MT_DATA_ACK) quit();

            // and the low 8 bits
            TWDR = reg;
            this -> status = transmit(I2C_DATA);
            if (this -> status != TW_MT_DATA_ACK) quit();

            // send start condition again.
            this -> status = transmit(I2C_START);
            if (this -> status == TW_MT_ARB_LOST) goto retry;
            if ((this -> status != TW_START) && (this -> status != TW_REP_START)) quit();

            // Send slave address (Read mode)
            TWDR = this -> deviceAddress | TW_READ;
            this -> status = transmit(I2C_DATA);
            if ((this -> status != TW_MR_SLA_NACK) || (this -> status == TW_MR_ARB_LOST))
               goto retry;
            if (this -> status != TW_MR_SLA_ACK) quit();

            // Retrive the data
            this -> status = transmit(I2C_DATA);
            if (this -> status != TW_MR_SLA_NACK) quit();

            return TWDR;
    }
}

#ifndef __I2C__
#define __I2C__

namespace base
{
    class AnotherI2C
    {
    public:
        void init();
        void TWIStart();
        void TWIStop();
        void TWIWrite(uint8_t data);
        uint8_t readACK();
        uint8_t readNACK();
        uint8_t getStatus();
    };
}
#endif

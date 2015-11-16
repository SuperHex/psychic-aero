#include "MultiSonar.h"

namespace algorithm
{
    bool MultiSonar::reachedSetHeight(uint8_t which)
    {
        if(this->height[which] >= this->setHeight) return true;
        else return false;
    }

    bool MultiSonar::overHeight(uint8_t which)
    {
        if(this->height[which] >= this->maxHeight) return true;
        else return false;
    }

    void MultiSonar::holdOn()
    {
        this->height[0] = this->s0.run();
        this->height[1] = this->s1.run();
        this->height[2] = this->s2.run();
        this->height[3] = this->s3.run();

    }
}

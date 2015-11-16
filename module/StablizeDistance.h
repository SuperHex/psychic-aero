#ifndef __SD__
#define __SD__

#include "sonar.h"
#include "PID.h"

namespace module
{
    class StablizeDistance : algorithm::PID<float>
    {
        StablizeDistance() : PID()
    };
}

#endif

#ifndef __MotorMap__
#define __MotorMap__

#include "../config/config.h"
#include "../util/util.template.hpp"

// We defined the motor as following order.
// Cross mode:
/* ------* front *------
 *        0    1
 *         \  /
 *          @
 *        /  \
 *      3     2
 * ------* rear *------
 */

// Direct mode:
/* -----* front *-----
 *          0
 *          |
 *      3 - @ - 1
 *          |
 *          2
 * -----* rear *-----
 */
namespace algorithm
{
    // What we do in this class is mapping pid control value to
    // each four motor's voltage(by setting PWM duty cycle).
    // Here we have defined two modes, CROSS_MODE and DIRECT_MODE.
    // In CROSS_MODE the copter will fly like 'X',
    // and in DIRECT_MODE it will behave like '+'.
    class MotorMap
    {
        bool mode;
        int16_t* throttle;
        base::container<float*> factors;
    public:
        MotorMap(int16_t  mode,
                 int16_t* throttle,
                 base::container<float*> factors);
        void setMode(bool m);
        void setThrottle(int16_t* t);
        void setFactor(base::container<float*>);
        // Run() takes PID output and return duty cycle
        // we should set to PWM regulator. Value greater
        // than 255 will be clamp to 255 since it represent
        // full power.
        void run(Vector& pid, double* result);
    };
}

#endif

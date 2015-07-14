#ifndef __PID__
#define __PID__

#include "../config/config.h"
#include "../base/container.hpp"
#include <math.h>
#include <util/delay.h>

namespace algorithm
{
    template<class T>
    class PID
    {
    private:
        base::container<float> factor;
        base::container<T> cont;
        T setpoint;
        T feedback;

    public:
        PID(T setpoint, float Kp, float Ki, float Kd)
        {
            this->setpoint      = setpoint;
            this->factor.get(0) = Kp;
            this->factor.get(1) = Ki;
            this->factor.get(2) = Kd;
        }
        T proportional(const T);
        T integral(const T);
        T derivative(const T);
        T calculate(const T);
    };

    template<class T>
    T PID<T>::proportional(const T val)
    {
        return val * this->factor.get(0);
    }

    template<class T>
    T PID<T>::integral(const T val)
    {
        this->cont.get(1) += (this->factor.get(1) * val * dt);
        return this->cont.get(1);
    }

    template<class T>
    T PID<T>::derivative(const T val)
    {
        auto v = atan2((val - this->cont.get(2)), dt) * this->factor.get(2);
        this->cont.get(2) = val;
        return v;
    }

    template<class T>
    T PID<T>::calculate(const T val)
    {
        auto v = val - (feedback + setpoint);
        T p,i,d;

        #ifdef P_CONTROL
        p = proportional(v);
        #endif

        #ifdef I_CONTROL
        i = integral(v);
        #endif

        #ifdef D_CONTROL
        d = derivative(v);
        #endif

        return p + i + d;
    }
}

#endif

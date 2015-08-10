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
    protected:
        base::container<float> factor;
        base::container<T> previous;
        T setpoint;
        T feedback;

    public:
        PID(T setpoint, float Kp, float Ki, float Kd)
        {
            this->setpoint  = setpoint;
            this->factor[0] = Kp / (Kp + Ki + Kd);
            this->factor[1] = Ki / (Kp + Ki + Kd);
            this->factor[2] = Kd / (Kp + Ki + Kd);
        }

        PID() : setpoint()
        {
            this->newFactor(0.3, 0.4, 0.3);
        }

        void newSetpoint(T);
        void newFactor(float Kp, float Ki, float Kd);
        T proportional(T);
        T integral(T);
        T derivative(T);
        T calculate(T);
    };

    template<class T>
    void PID<T>::newSetpoint(T val)
    {
        this->setpoint = val;
    }

    template<class T>
    void PID<T>::newFactor(float Kp, float Ki, float Kd)
    {
        this->factor[0] = Kp / (Kp + Ki + Kd);
        this->factor[1] = Ki / (Kp + Ki + Kd);
        this->factor[2] = Kd / (Kp + Ki + Kd);
    }

    template<class T>
    T PID<T>::proportional(T val)
    {
        return val * this->factor[0];
    }

    template<class T>
    T PID<T>::integral(T val)
    {
        this->previous[1] = this->previous[1] + (val * this->factor[1] * dt);
        return this->previous[1];
    }

    template<class T>
    T PID<T>::derivative(T val)
    {
        T v = (val - this->previous[2]) * this->factor[2];
        this->previous[2] = val;
        return v;
    }

    template<class T>
    T PID<T>::calculate(T val)
    {
        T v = val - (feedback + setpoint);
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

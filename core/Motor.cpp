#include "Motor.h"

namespace core
{
    void Motor::holdOn()
    {
        this->holdOn(this->setpoint);
    }

    void Motor::holdOn(base::container<float> plane)
    {
        this->angle = this->toAngle(this->getRaw(measure), this->angle);
        this->newSetpoint(plane);
        base::container<float> diff = this->calculate(angle);
        this->MotorMap::run(diff, this->res);
        if(!this->started)
        {
            this->PWM::run(PIN_3, 0.25, FAST_PWM);
            this->PWM::run(PIN_5, 0.25, FAST_PWM);
            this->PWM::run(PIN_6, 0.25, FAST_PWM);
            this->PWM::run(PIN_9, 0.25, FAST_PWM);
        }
        if(this->started)
        {
            this->setDutyCycle(PIN_3, this->res[0]);
            this->setDutyCycle(PIN_5, this->res[1]);
            this->setDutyCycle(PIN_6, this->res[2]);
            this->setDutyCycle(PIN_9, this->res[3]);
        }
    }
}

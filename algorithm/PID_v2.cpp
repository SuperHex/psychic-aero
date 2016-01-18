#ifndef __PID_v2__
#define __PID_v2__

namespace algorithm
{
    #define PIDMODE 1
    #define PIMODE  2
    #define PDMODE  3
    #define PMODE   4

    template< typename Type, class Process >
    struct PID
    {
    private:
        float factor[3];
        Type pre_i;
        Type pre_d;
        Type setpoint;
        Type output;
        Process f;

    public:
        PID(float Kp, float Ki, float Kd) : factor{Kp,Ki,Kd}, pre_i(), pre_d(), output() { }

        Type p(const Type& err)
        {
            return factor[0] * err;
        }

        Type i(const Type& err)
        {
            pre_i += err;
            return factor[1] * pre_i;
        }

        Type d(const Type& err)
        {
            return factor[2] * (err - pre_d);
        }

        Type calculate(const Type& in, int mode)
        {
            Type err = setpoint - in;
            switch (mode)
            {
                case PIDMODE:
                    output = f.process(p(err) + i(err) + d(err));
                    break;
                case PIMODE:
                    output = f.process(p(err) + i(err));
                    break;
                case PDMODE:
                    output = f.process(p(err) + d(err));
                    break;
                case PMODE:
                    output = f.process(p(err));
                    break;
            }
            return output;
        }
    };
}

#endif

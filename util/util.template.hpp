#ifndef __util__
#define __util__

namespace util
{
    template<typename T>
    T scale(T val,
             const T min, const T max,
             const T minBound, const T maxBound)
    {
        if(val > max) val = max;
        if(val < min) val = min;
        return (val * (max - min) / (maxBound - minBound));
    }
}

#endif

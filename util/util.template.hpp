#ifndef __util__
#define __util__

#include "../base/container.hpp"

namespace util
{
    template<typename T, typename U>
    U scale(T val,
             const T min, const T max,
             const U minBound, const U maxBound)
    {
        if(val > max) val = max;
        if(val < min) val = min;
        return (val * (max - min) / (maxBound - minBound));
    }

    template<typename T>
    base::container<T> operator*(const T& left, const base::container<T>& right)
    {
        base::container<T> opt = {right[0] * left,
                                  right[1] * left,
                                  right[2] * left};
        return opt;
    }
}

#endif

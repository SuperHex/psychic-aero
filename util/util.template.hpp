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

    // fmap :: (a -> b) -> f a -> f b
    template< typename Func,
              typename U,
              template< typename ... > class T >
    T<U> fmap(const Func& function, const T<U>& t)
    {
        T<U> res;
        res.push_back(function(t.begin()));
        if (t.next() != nullptr) // nullptr is not good
        {
            fmap(function, t.move_next(1));
        }
        return res;
    }

    // foldr :: (a -> b -> b) -> b -> t a -> b
    template< typename Func,
              typename Ta,
              typename Tb,
              template< typename ... > class T >
    Tb foldr(Func function, Tb b, T<Ta> t)
    {
        if (t.begin() == nullptr) // maybe monoid instead ?
        {
            return b;
        }
        else
        {
            return function(t.begin(), foldr(function, b, t.move_next(1)));
        }
    }
}

#endif

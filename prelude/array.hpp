#pragma once

#include "utility.hpp"
#include "exception.hpp"
#include "typeclass.hpp"

#define __instance public

namespace prelude
{
    
    template <class T, unsigned N>
    struct array : __instance Functor<array<T,N>>
    {
        typedef T  type;
        typedef T* iterator;
        typedef const T* const_iterator;
        
        array()
        : _array(new T[N]) { }
        array(const array<T,N>& other)
        : _array(other._array ? other._array : nullptr) { }
        array(array<T,N>&& other)
        : _array(other._array) { delete[] other._array; other._array = nullptr; }
        
        template <class ... Us>
        array(Us && ... vs)
        {
            _array = new T[N];
            static_assert(sizeof ... (vs) <= N, "initialize with too much value");
            process(0, prelude::forward<Us>(vs) ... );
        }
        ~array() { delete[] _array; }
        
        array<T,N>& operator=(const array<T,N>& other);
        array<T,N>& operator=(array<T,N>&& other);
        inline T operator[](unsigned position) const;
        array<T,N>& operator+(const array<T,N>& other);
        array<T,N>& operator-(const array<T,N>& other);
        T* operator*() = delete;
        T* operator->() = delete;
        
        bool operator==(const array<T,N>& other)
        {
            for (auto i = 0; i < N; i++)
            {
                if ((*this)[i] != other[i])
                    return false;
            }
            return true;
        }
        
        constexpr T* begin() const noexcept { return _array; }
        constexpr T* end() const noexcept { return _array + N; }
        
        template <class B>
        array<B,N>&& fmap_impl(prelude::function<B(T)>&& func, array<T,N>& arr)
        {
            array<B,N> result;
            for (auto i = 0; i < N; i++)
            {
                result[i] = func(arr[i]);
            }
            return prelude::move(result);
        }
        
        void set(unsigned pos, T val)
        {
            if (pos < N)
            {
                _array[pos] = val;
            }
            else
            {
                // TODO: better exception
                throw;
            }
        }
        
    private:
        // it should be replaced by a unique_ptr.
        T* _array = nullptr;
        
        template <class U, class ... Us>
        void process(unsigned offset, U&& v, Us&& ... vs)
        {
            if (offset <= N - 1)
            {
                *(_array + offset) = v;
                process(++offset, prelude::forward<Us>(vs) ... );
            }
        }
        
        void process(unsigned offset) { }
    };
    
    template <class T>
    struct array<T,0> {};
    
    template <class T, unsigned N>
    array<T,N>& array<T,N>::operator=(const array<T,N>& other)
    {
        for (auto idx = 0; idx < N; idx++)
        {
            this->_array[idx] = other[idx];
        }
        return *this;
    }
    
    template <class T, unsigned N>
    array<T,N>& array<T,N>::operator=(array<T,N>&& other)
    {
        if (_array != other._array)
        {
            delete[] this->_array;
            this->_array = nullptr;
            prelude::swap(this->_array, other._array);
        }
        return *this;
    }
    
    template <class T, unsigned N>
    inline T array<T,N>::operator[](unsigned position) const
    {
        if (_array && (position < N))
        {
            return _array[position];
        }
        else
        {
            throw new exception("array: index out of bound");
        }
    }
    
    // template <class B, class A, unsigned N, class Function>
    // inline array<B,N> fmap(Function f, array<A,N>& a)
    // {
    //   array<B,N> res;
    //   auto iter_res = res.begin();
    //   for (auto iter = a.begin(); iter != a.end(); iter++, iter_res++)
    //     {
    //       *iter_res = f(*iter);
    //     }
    //   return res;
    // }
    
    template <class T, class Function>
    T liftA2(Function f, const T& x, const T& y)
    {
        auto iter_x = x.begin();
        auto iter_y = y.begin();
        T z;
        auto iter_z = z.begin();
        for (; iter_x != x.end() && iter_y != y.end(); iter_x++, iter_y++, iter_z++)
        {
            *iter_z = f(*iter_x, *iter_y);
        }
        return z;
    }
    
    template <class T, unsigned N>
    array<T,N>& array<T,N>::operator+(const array<T,N>& other)
    {
        auto add = [](T lhs, T rhs) { return lhs + rhs; };
        *this = liftA2(add, *this, other);
        return *this;
    }
    
    template <class T, unsigned N>
    array<T,N>& array<T,N>::operator-(const array<T,N>& other)
    {
        auto sub = [](T lhs, T rhs) { return lhs - rhs; };
        *this = liftA2(sub, *this, other);
        return *this;
    }
}

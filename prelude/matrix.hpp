//
//  matrix.hpp
//  Prelude
//
//  Created by Ryan Wang on 2016/10/31.
//  Copyright © 2016年 Cirno. All rights reserved.
//

#pragma once

#include "array.hpp"
#include "function.hpp"
#include "pointer.hpp"
#include "typeclass.hpp"
#include <math.h>

#include <iostream>

#if DEBUG
#include <assert.h>
#endif

#define _ARRAY_POS(x,y,row) ( ((x-1) * row) + (y - 1) )

namespace prelude
{
    using prelude::unique_ptr;
    using prelude::array;
    
    template <class _Tp, unsigned M, unsigned N>
    struct matrix
    {
        matrix() : store_(new array<_Tp,M*N>) { }
        
        matrix(matrix<_Tp,M,N>&& other) : store_()
        { prelude::swap(store_, other.store_); }
        
        matrix(const matrix<_Tp,M,N>& other) : store_(new array<_Tp,M*N>)
        {
            for (auto row = 1; row <= M; row++)
            {
                for (auto col = 1; col <= N; col++)
                {
                    set(row,col,
                        other(row,col)
                        );
                }
            }
        }
        
        template <class U, class ... Us>
        explicit matrix(U u, Us ... us) :
        store_(new array<_Tp, M*N>(prelude::forward<U>(u), prelude::forward<Us>(us) ...)) { }
        
        matrix<_Tp,M,N>& operator=(const matrix<_Tp,M,N>& other)
        {
            *store_ = *(other.store_);
            return *this;
        }
        
        matrix<_Tp,M,N>& operator=(matrix<_Tp,M,N>&& other)
        {
            if (store_ != other.store_)
            {
                prelude::swap(store_, other.store_);
            }
            return *this;
        }
        
        _Tp operator()(unsigned row, unsigned col) const
        {
            return (*store_)[_ARRAY_POS(row, col, N)];
        }
        
        inline void set(unsigned row, unsigned col, _Tp val)
        {
            // TODO: better error
            (row <= M && col <= N) ? (*store_).set(_ARRAY_POS(row, col, N), val) : throw;
        }
        
        matrix<_Tp,M,N>& operator+(const matrix<_Tp,M,N>& other)
        {
            *store_ = *store_ + *(other.store_);
            return *this;
        }
        
        matrix<_Tp,M,N>& operator-(const matrix<_Tp,M,N>& other)
        {
            *store_ = *store_ - *(other.store_);
            return *this;
        }
        
        bool operator==(const matrix<_Tp,M,N>& other)
        {
            return *store_ == *(other.store_);
        }
        
        bool operator!=(const matrix<_Tp,M,N>& other)
        {
            return !(*this == other);
        }
        
        matrix<_Tp,1,N> row(unsigned n)
        {
            // make sure matrix has the n th row
            if (n <= M)
            {
                matrix<_Tp,1,N> tmp{};
                
                for (auto i = 1; i <= N; i++)
                {
                    tmp.set(1, i, (*this)(n, i));
                }
                return tmp;
            }
            else
            {
                // TODO: throw a specific error
                throw;
            }
        }
        
        matrix<_Tp, M-1, N> remove_row(unsigned index)
        {
            #if DEBUG
            assert(index <= M);
            #endif
            
            matrix<_Tp, M-1, N> tmp{};
            for (auto row = 1; row <= M; row++)
            {
                for (auto col = 1; col <= N; col++)
                {
                    if (row != index)
                    {
                        row < index ?
                          tmp.set(row, col, (*this)(row,col))
                        : tmp.set(row - 1 , col, (*this)(row,col));
                    }
                }
            }
            return tmp;
        }
        
        matrix<_Tp, M, N-1> remove_col(unsigned index)
        {
            #if DEBUG 
            assert(index <= N);
            #endif
            
            matrix<_Tp, M, N-1> tmp{};
            for (auto row = 1; row <= M; row++)
            {
                for (auto col = 1; col <= N; col++)
                {
                    if (col != index)
                    {
                        col < index ?
                            tmp.set(row, col, (*this)(row,col))
                        :   tmp.set(row, col - 1, (*this)(row,col));
                    }
                }
            }
            return tmp;
        }
        
        matrix<_Tp,M,1> col(unsigned n)
        {
            // make sure matrix has the n th column
            if (n <= N)
            {
                // copy and retur as rvalue reference
                matrix<_Tp,M,1> tmp;
                for (auto i = 1; i < M + 1; i++)
                {
                    tmp.set(i, 1, (*this)(i, n));
                }
                return tmp;
            }
            else
            {
                // TODO: throw a specific error
                throw;
            }
        }
        
        template <unsigned R, unsigned C>
        matrix<_Tp, R, C> submatrix(unsigned from_row, unsigned from_col)
        {
            static_assert(R <= M && C <= N, "submatrix is too large");
            matrix<_Tp, R, C> tmp{};
            for (auto r = from_row; (r < from_row + R) && (r <= M); r++)
            {
                for (auto c = from_col; (c < from_col + C) && (c <= N); c++)
                {
                    tmp.set(r - from_row + 1, c - from_col + 1, (*this)(r,c));
                }
            }
            return tmp;
        }
        
        template <unsigned N_>
        matrix<_Tp, M, N + N_> left_adjoint(const matrix<_Tp, M, N_>& other)
        {
            matrix<_Tp, M, N + N_> tmp{};
            for (auto row = 1; row <= M; row++)
            {
                for (auto col = 1; col <= N + N_; col++)
                {
                    tmp.set(row, col,
                            col <= N ?
                                (*this)(row,col)
                            :   other(row,col - N)
                            );
                }
            }
            return tmp;
        }
        
        template <unsigned N_>
        matrix<_Tp, M, N + N_> right_adjoint(const matrix<_Tp, M, N_>& other)
        {
            matrix<_Tp, M, N + N_> tmp{};
            for (auto row = 1; row <= M; row++)
            {
                for (auto col = 1; col <= N + N_; col++)
                {
                    tmp.set(row, col,
                            col <= N_ ?
                            other(row,col)
                            :   (*this)(row,col - N_)
                            );
                }
            }
            return tmp;
        }
        
        template <unsigned N_>
        friend matrix<_Tp,M,N_>
        operator*(const matrix<_Tp,M,N>& lhs, const matrix<_Tp,N,N_>& rhs)
        {
            matrix<_Tp,M,N_> tmp{};
            _Tp acc = 0;
            for (auto row = 1; row < M + 1; row++)
            {
                for (auto col_ = 1; col_ < N_ + 1; col_++)
                {
                    for (auto col = 1; col < N + 1; col++)
                    {
                        acc += lhs(row,col) * rhs(col,col_);
                    }
                    tmp.set(row, col_, acc);
                    acc = 0;
                }
            }
            return tmp;
        }
        
        matrix<_Tp, M, N>& operator*(_Tp scalar)
        {
            for (auto row = 1; row <= M; row++)
            {
                for (auto col = 1; col <= N; col++)
                {
                    set(row,col,
                        (*this)(row,col) * scalar
                        );
                }
            }
            return *this;
        }
        
        template <class _T, unsigned R, unsigned C>
        friend matrix<_T, R, C>& operator*(_T scalar, matrix<_T, R, C>&& m)
        {
            return m * scalar;
        }
        
        matrix<_Tp,N,M> transpose() const noexcept
        {
            matrix<_Tp,N,M> tmp;
            for (auto row = 1; row < M + 1; row++)
            {
                for (auto col = 1; col < N + 1; col++)
                {
                    tmp.set(row,col, (*this)(col,row));
                }
            }
            return tmp;
        }
        
        friend std::ostream& operator<<(std::ostream& os, const matrix<_Tp, M, N>& m)
        {
            for (auto row = 1; row <= M; row++)
            {
                os << "[";
                for (auto col = 1; col <= N; col++)
                {
                    os << m(row,col) << " " ;
                }
                os << "]" << std::endl;
            }
            return os;
        }

        _Tp determinant() noexcept;
        matrix<_Tp, M, N> cofactor() noexcept;
        matrix<_Tp, M, N> adjugate() noexcept { return cofactor().transpose(); }
        matrix<_Tp, M, N> inverse();
    protected:
        unique_ptr<array<_Tp, M*N>> store_;
    };
    
    template <class _Tp>
    struct matrix<_Tp,1,1>
    {
        matrix() : store_(0) { }
        explicit matrix(_Tp val) : store_(val) { }
        matrix(const matrix<_Tp,1,1>& other) : store_(other.store_) { }
        matrix(matrix<_Tp,1,1>&& other) : store_(prelude::move(other.store_)) { }
        _Tp operator()(unsigned row, unsigned col) const { return store_; }
        _Tp determinant() noexcept { return store_; }
        void set(unsigned row, unsigned col, _Tp val) { store_ = val; }
    private:
        _Tp store_;
    };
    
    template <class _Tp, unsigned M, unsigned N>
    _Tp matrix<_Tp, M, N>::determinant() noexcept
    {
        static_assert( M == N, "Matrix must be square");
        
        _Tp result = 0;
        
        for (auto col = 1; col <= N; col++)
        {
            auto factor = static_cast<_Tp>(pow(-1, col + 1)) * (*this)(1,col);
            auto sub = remove_row(1).remove_col(col).determinant();
            result += factor * sub;
        }
        return result;
    }
    
    template <class _Tp, unsigned M, unsigned N>
    matrix<_Tp, M, N> matrix<_Tp, M, N>::cofactor() noexcept
    {
        matrix<_Tp, M, N> tmp{};
        
        for (auto row = 1; row <= M; row++)
        {
            for (auto col = 1; col <= N; col++)
            {
                tmp.set(row,col,
                        static_cast<_Tp>(pow(-1, row + col)) *
                        remove_row(row).remove_col(col).determinant()
                        );
            }
        }
        return tmp;
    }
    
    template <class _Tp, unsigned M, unsigned N>
    matrix<_Tp, M, N> matrix<_Tp, M, N>::inverse()
    {
        auto d = determinant();
        if (d == 0) { throw; }
        else
        {
            return (1.0 / d) * adjugate();
        }
    }
}

template <class T> using Matrix3x3 = prelude::matrix<T,3,3>;

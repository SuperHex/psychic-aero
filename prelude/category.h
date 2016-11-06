#pragma once

#include "function.hpp"

namespace prelude
{

  template <class T>
  inline T id (const T& x)
  {
    return x;
  }

  template <class T>
  inline T id (T x)
  {
    return x;
  }

  template <class A, class B, class C>
  inline function<C(A)> compose(function<B(A)>& f, function<C(B)>& g)
  {
    auto tmp = [&f,&g](A x) { return f( g(x) ); };
    return tmp;
  }
}

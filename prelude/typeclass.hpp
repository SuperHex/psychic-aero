#pragma once

#include "function.hpp"
#include "utility.hpp"

#define __INVOKE_DERIVED(func) static_cast<Derived*>(this)->func
#define _instance public

namespace prelude
{
  template <class T> struct Functor { };

  template <template <typename> class Derived, class A>
  struct Functor<Derived<A>>
  {
    template <class B>
    Derived<B>&& fmap(prelude::function<B(A)>&& func)
    {
      return static_cast<Derived<A>*>(this)->fmap_impl( prelude::forward(func));
    }
  };

  template <template <typename> class _Tp, class A, class B>
  _Tp<B>&& fmap(Functor<_Tp<A>>& functor, prelude::function<B(A)>&& func)
  {
    return prelude::move(functor.fmap(prelude::forward(func)));
  }

  template <class Derived>
  struct Monoid
  {
    Derived&& mempty()
    {
      return __INVOKE_DERIVED(mempty_impl());
    }

    Derived&& mappend(Derived& m, Derived& n)
    {
      return __INVOKE_DERIVED(mappend_impl( prelude::forward(m)
                                          , prelude::forward(n)
                                          )
                             );
    }
  };

  template <class _Tp>
  _Tp&& mempty(Monoid<_Tp>& monoid)
  {
    return prelude::move(monoid.mempty());
  }

  template <class _Tp>
  _Tp&& mappend(Monoid<_Tp>& monoid, _Tp& m, _Tp& n)
  {
    return prelude::move(monoid.mappend( prelude::forward(m)
                                       , prelude::forward(n)
                                       )
                        );
  }

  template <class Derived>
  struct Foldable : public Monoid<Derived>
  {
    template <class M>
    M&& foldMap(prelude::function<M(typename Derived::element_type)> func, Derived& ta)
    {
      return __INVOKE_DERIVED(foldMap_impl(prelude::forward(func), prelude::forward(ta)));
    }
  };

  template <class M, class _Tp>
  M&& foldMap(Foldable<_Tp>& f, prelude::function<M(typename _Tp::element_type)> func, _Tp& ta)
  {
    return prelude::move(f.foldMap(prelude::forward(func), prelude::forward(ta)));
  }
}

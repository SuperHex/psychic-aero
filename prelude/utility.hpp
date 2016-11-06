#pragma once

namespace prelude
{
  template <class T> struct remove_reference { typedef T type; };
  template <class T> struct remove_reference<T&> { typedef T type; };
  template <class T> struct remove_reference<T&&> { typedef T type; };

  template <class _Tp>
  constexpr typename remove_reference<_Tp>::type&&
  move(_Tp&& __t) noexcept
  { return static_cast<typename remove_reference<_Tp>::type&&>(__t); }

  /*
   * fake std::forward<T>, used to make argument type as it is when passing around.
   * personally, I would like to call it "co-move",
   * since it's type is a concomitant of "move".
   */
  template <class _Tp>
  constexpr _Tp&&
  forward(typename remove_reference<_Tp>::type& __t) { return static_cast<_Tp&&>(__t); };

  template <class T> void swap(T& a, T&b)
  {
    T tmp(move(a)); a = move(b); b = move(tmp);
  }

  template <class T, unsigned N> void swap(T (&a)[N], T (&b)[N])
  {
    for (auto i = 0; i < N; i++) { swap(a[i], b[i]); }
  }
}

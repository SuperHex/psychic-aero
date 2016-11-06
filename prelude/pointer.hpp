#pragma once

#include "utility.hpp"

namespace prelude
{

  // OK let's make a nullptr...
  struct nullptr_t
  {
    template <class T> operator T *() { return 0; }
    template <class T, class C> operator T C::*() { return 0; }
  };

  //static nullptr_t nullptr;

    
  // simple smart pointer
  template <class _Tp>
  struct unique_ptr
  {
    
    unique_ptr() : ptr_(nullptr) { }
    unique_ptr(_Tp* ptr) : ptr_(ptr) { };
    unique_ptr(const unique_ptr<_Tp>&) = delete;
    unique_ptr(unique_ptr<_Tp>&& other) : ptr_(nullptr)
    {
      prelude::swap(ptr_, other.ptr_);
    }
    
    ~unique_ptr() { delete ptr_; }
    
    _Tp& operator*() const noexcept { return *ptr_; }
    _Tp* operator->() const noexcept { return ptr_; }
    
    bool operator==(const unique_ptr<_Tp>& other)
    {
      return ptr_ == other.ptr_;
    }
    
    bool operator!=(const unique_ptr<_Tp>& other)
    {
      return !(*this == other);
    }
    
    unique_ptr<_Tp>& operator=(const unique_ptr<_Tp>&) = delete;
    unique_ptr<_Tp>& operator=(unique_ptr<_Tp>&& other)
    {
      if (other.ptr_ != ptr_)
      {
        delete ptr_;
        ptr_ = nullptr;
        prelude::swap(ptr_, other.ptr_);
      }
      return *this;
    }
    
    _Tp* get() const noexcept { return ptr_; }
    inline void release() noexcept { delete ptr_; ptr_ = nullptr; }
    void reset(_Tp* ptr) noexcept
    {
      release();
      ptr_ = ptr;
    }
    
  private:
    _Tp* ptr_ = nullptr;
  };
  
  template <class _Tp>
  struct unique_ptr<_Tp []>
  {
    // use prelude::array instead
  };
}

#pragma once

#include "exception.hpp"

namespace prelude
{

  template <class Result>
  struct function_traits
  {
    typedef Result type;
  };

  template <class Result, class ... Arguments>
  struct function_traits<Result(Arguments ...)>
  {
    typedef Result (*type)(Arguments ...);
  };

  template <class Result, class ... Arguments>
  struct IFunction
  {
    virtual Result operator()(Arguments ... args) = 0;
    virtual IFunction* fork() const = 0;
    virtual ~IFunction() = default;
  };

  template <class Func, class Result, class ... Arguments>
  struct concrete : public IFunction<Result, Arguments ...>
  {
    concrete (const Func& f) : _function(f) {}
    inline Result operator()(Arguments... args) override
    {
      return _function(args...);
    }

    concrete* fork() const override
    {
      return new concrete(_function);
    }

  private:
    Func _function;
  };

  template <typename>
  struct function{};

  template <class Result, class ... Args>
  struct function<Result(Args...)>
  {
    function()
      : _function(nullptr)
    { }

    template <class Func> function(const Func& f)
      : _function(new concrete<typename function_traits<Func>::type, Result, Args...>(f))
    { }

    function (const function& rhs)
      : _function( rhs._function ? rhs._function->fork() : nullptr)
    { }

    function& operator=(const function& rhs)
    {
      if ( rhs._function && (&rhs != this))
        {
          delete _function;
          _function = rhs._function->fork();
        }
      return *this;
    }

    template <class Func>
    function& operator=(const Func& f)
    {
      delete _function;
      _function = new concrete<typename function_traits<Func>::type, Result, Args...>(f);
      return *this;
    }

    Result operator()(Args... args)
    {
      if (_function)
        {
          return (*_function)(args...);
        }
      else
        {
          throw new exception ("try to applicate a null function pointer.");
        }
    }

    ~function() { delete _function; }

  private:
    IFunction<Result, Args...>* _function;
  };
}

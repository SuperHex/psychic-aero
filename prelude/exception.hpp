#pragma once

#include <string>

namespace prelude
{

  /*  exception type supplicate the std one.
   *  should be initialized with an error message.
   */
  struct exception
  {
    exception(std::string str) : _error(str) { }
    inline std::string what() const { return _error; }
  private:
    std::string _error = "General exception without additional information.";
  };
}

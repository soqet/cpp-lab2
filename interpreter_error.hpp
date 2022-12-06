#pragma once

#include <stdexcept>
#include <string>

class InterpreterError: public std::runtime_error {
  public:
    // CR: explicit
    InterpreterError(const std::string & msg): std::runtime_error(msg) {}
};

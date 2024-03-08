#pragma once

#include <exception>
#include <string>

namespace quadeq {

class NoSolution : public std::logic_error { // Это исключение, когда нет решения уравнения
 public:
    NoSolution(std::string message): std::logic_error{std::move(message)} {

    }
};

}  // namespace quadeq
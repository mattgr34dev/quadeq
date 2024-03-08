#pragma once

#include <quadeq/export.h>
#include <quadeq/solution.hpp>

namespace quadeq {

struct EquationParams { // Это структура которая описывает уравнения
  double a = 0;
  double b = 0;
  double c = 0;
};

class Solver { // Это класс который решает уравнения
 public:
  static Solution SolveQuadratic(const EquationParams params);
  static Solution SolveBiquadratic(const EquationParams params);
};

} // namespace quadeq

#pragma once

#include <vector>

namespace quadeq {

enum class EquationType { // Это класс, который хранит в себе тип уравнения
  kLinear,
  kQuadratic,
  kBiquadratic
};

class SolutionBuilder;

class Solution { // Этот класс возвращает корни пользователю
 public:
  EquationType GetEquationType() const noexcept;
  const std::vector<double>& GetRoots() const;

 private:
  friend class SolutionBuilder;

  EquationType equation_type_;
  std::vector<double>& roots_;
};

}  // namespace quadeq
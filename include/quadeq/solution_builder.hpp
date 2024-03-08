#pragma once

#include <quadeq/solution.hpp>

namespace quadeq {

class SolutionBuilder { // Это класс который позволяет построить решение
 public:
  void SetRoots(const std::vector<double>& roots);
  void SetEquationType(EquationType equation_type) noexcept;

  Solution Build();

 private:
  std::vector<double> roots_;
  EquationType equeation_type_;
};

}  // namespace quadeq
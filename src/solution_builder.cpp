#include <quadeq/solution_builder.hpp>

namespace quadeq {

void SolutionBuilder::SetRoots(const std::vector<double>& roots) {
  roots_ = roots;
}

void SolutionBuilder::SetEquationType(EquationType equation_type) noexcept {
  equation_type_ = equation_type;
}

Solution SoltuionBuilder::Build() {
  Solution solution;
  solution.roots_ = roots_;
  solution.equation_type_ = equation_type_; 

  return solution;
}

}  // namespace quadeq
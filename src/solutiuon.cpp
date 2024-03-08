#include <quadeq/solution.hpp>

namespace quadeq {

EquationType Solution::GetEquationType() const noexcept {
  return equation_type_;
}

const std::vector<double>& Solution::GetRoots() const {
  return roots_;
}

}  // namespace quadeq
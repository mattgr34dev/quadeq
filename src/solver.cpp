#include <quadeq/solver.hpp>

#include <cmath>

#include <quadeq/exception.hpp>
#include <quadeq/solution_builder.hpp>

namespace quadeq {

namespace {

double SolveLinear(double a, double b) noexcept {
  return -1*c / b; // Возвращаем решение
} 

}  // namespace

Solution Solver::SolveQuadratic(const EquationParams params) {
  SolutionBuilder builder;

  if (params.a == 0) {
    if (params.b == 0) {
      throw NoSolution{"'b' can not be '0' in linear equation."}; /* Если переменная b = 0, то мы возвращаем пользователю сообщение, 
      что решений нет. */
    }

    builder.SetEquationType(EquationType::kLinear); // Задаём тип уравнения - линейный
    builder.SetRoots({SolveLinear(params.b, params.c)}); // Решаем это уравнение
    return builder.Build(); // Возвращаем решению
  }

  double d = params.b * params.b - 4 * params.a * params.c; // Вычисляем дискриминант

  if (d < 0) {
    throw NoSolution{"Roots does not exist, because Descriminant is 0."}; /* Если дискриминант = 0, то возвращаем пользователю сообщение, 
    что решенийн нет. */
  }

  builder.SetEquationType(EquationType::kQuadratic); // Задаём тип уравнения - квадратный

  if (d == 0) {
    double x = (-1 * params.b) / 2 * params.a; // Вычисляем корни
    builder.SetRoots({x}); // Возвращаем корни
  } else {
    double x1 = (-1 * params.b + std::sqrt(d)) / 2 * params.a; // Вычисляем корни
    double x2 = (-1 * params.b - std::sqrt(d)) / 2 * params.a; // Вычисляем корни
    builder.SetRoots({x1, x2}); // Возвращаем корни
  }

  return builder.Build(); // Возвращаем пользователю решение
}

Solution Solver::SolveBiquadratic(const EquationParams params) {
  SolutionBuilder builder;

  if (params.a == 0) {
    return SolveQuadratic({.a=params.b, .b=0, .c=params.c}); /* Если параметр а = 0, то мы возвращаем функцию решения обычного квадратного 
     и меняем коэф. местами */
  }

  double d = params.b * params.b - 4 * params.a * params.c; // Вычисляем дискриминант

  if (d < 0) {
    throw NoSolution{"Roots does not exist, because Descriminant is 0."}; /* Если дискриминант = 0, то возвращаем пользователю сообщение, 
    что решений нет. */
  }

  builder.SetEquationType(EquationType::kBiquadratic); // Задаём тип уравнения - биквадратное

  if (d == 0) {
    double t = (-1 * params.b) / 2 * params.a; // Вычисляем t 

    double x1 = sqrt(t); // Вычисляем корни
    double x2 = -1 * sqrt(t); // Вычисляем корни
    builder.SetRoots({x1, x2}) // Возвращаем корни
  } else {
    double t1 = (-1 * params.b + std::sqrt(d)) / 2 * params.a; // Вычисляем t 
    double t2 = (-1 * params.b - std::sqrt(d)) / 2 * params.a; // Вычисляем t 

    double x1 = sqrt(t1); // Вычисляем корни
    double x2 = sqrt(t2); // Вычисляем корни
    double x3 = -1 * sqrt(t1); // Вычисляем корни
    double x4 = -1 * sqrt(t2); // Вычисляем корни
    builder.SetRoots({x1, x2, x3, x4}); // Возвращаем корни
  }

  return builder.Build(); // Возвращаем пользователю решение
}

} // namespace quadeq

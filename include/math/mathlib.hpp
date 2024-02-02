#ifndef INCLUDE_MATH_MATHLIB_H_
#define INCLUDE_MATH_MATHLIB_H_

/// @brief Generates a double from the normal distribution
/// @param mean the mean of the distribution (μ)
/// @param sd the standard deviation (σ)
/// @return a random double
double boost_normal_distribution(double mean = 0.0, double sd = 1.0);

/// @brief Generates an integer between min and max
/// @param max the max value (inclusive)
/// @param min the min value (inclusive)
/// @return a random integer
int boost_uniform_int_distribution(int max = 10, int min = 1);

#endif  // INCLUDE_MATH_MATHLIB_H_

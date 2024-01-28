#ifndef INCLUDE_MATH_MATHLIB_H_
#define INCLUDE_MATH_MATHLIB_H_

/// @brief 
/// @param mean the mean of the distribution (μ)
/// @param sd the standard deviation (σ)
/// @return 
double boost_normal_distribution(double mean = 0.0, double sd = 1.0);

int boost_uniform_int_distribution(int high = 10, int low = 1);

#endif  // INCLUDE_MATH_MATHLIB_H_

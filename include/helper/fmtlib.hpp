#ifndef INCLUDE_HELPER_FMT_H_
#define INCLUDE_HELPER_FMT_H_

#include <string>

/// @brief Formats the input value with the desired precision to a string
/// @param val the input value
/// @param precision the desired precision (number of digits in total)
/// @return a string of the value
std::string Formatter(double val, const char precision = 3);

#endif  // INCLUDE_HELPER_FMT_H_
#ifndef INCLUDE_COORDINATE_GENERATORLIB_H_
#define INCLUDE_COORDINATE_GENERATORLIB_H_

#include "coordinate/vectorlib.hpp"

/// @brief Generate the Next Circle That Is Connected to the Start
/// @param start the center of the first circle
/// @param radiusStart the raduis of the start circle
/// @param dir the direction from the start to the end
/// @param radius the raduis of the new circle
/// @return the center of the new circle
Vector GenerateNextCircle(const Vector& start, const double radiusStart, const Vector& dir = Vector(1.0, 0.0), double radiusNew = 1.0);

#endif  // INCLUDE_COORDINATE_GENERATORLIB_H_

#include "coordinate/generatorlib.hpp"

#include "coordinate/vectorlib.hpp"

Vector GenerateNextCircle(const Vector& start, const double radiusStart, const Vector& dir, double radiusNew)
{
    auto u = dir.Unit();
    auto distance = radiusStart + radiusNew;
    return start + distance * u;
}
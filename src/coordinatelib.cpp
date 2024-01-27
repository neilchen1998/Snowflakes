#include <cmath>

#include "coordinate/coordinatelib.hpp"

Point::Point() : x(0), y(0) {}

Point::Point(double x, double y) : x(x), y(y) {}

double Point::Distance(const Point& other)
{
    return sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
}

double Point::Magnitude() const
{
    return sqrt((x) * (x) + (y) * (y));
}

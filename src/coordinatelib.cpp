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

Point Point::Unit() const
{
    return Point(this->x / Magnitude(), this->y / Magnitude());
}

Point Point::operator+(const Point& p)
{
    return Point(this->x + p.x, this->y + p.y);
}

Point Point::operator-(const Point& p)
{
    return Point(this->x - p.x, this->y - p.y);
}

Point Point::operator+=(const Point& p)
{
    this->x += p.x;
    this->y += p.y;

    return *this;
}

Point Point::operator-=(const Point& p)
{
    this->x -= p.x;
    this->y -= p.y;

    return *this;
}

Point Point::operator*(double c)
{
    return Point(this->x * c, this->y * c);
}

Point Point::operator*=(double c)
{
    this->x *= c;
    this->y *= c;

    return *this;
}

Point operator*(double c, const Point& p)
{
    return Point(p.x * c, p.y * c);
}

double Point::operator*(const Point& p) const
{
    return this->x * p.x + this->y * p.y;
}

bool operator==(const Point& a, const Point& b)
{
    return (a.x == b.x) && (a.y == b.y);
}

bool operator!=(const Point& a, const Point& b)
{
    return (a.x != b.x) || (a.y != b.y);
}
#include <cmath>
#include <string>
#include <sstream>

#include "coordinate/vectorlib.hpp"
#include "helper/fmtlib.hpp"

#define PI 3.14159265

Vector::Vector() : x(0), y(0) {}

Vector::Vector(double x, double y) : x(x), y(y) {}

Vector::Vector(const Vector& other) : x(other.x), y(other.y) {}

double Vector::Distance(const Vector& other)
{
    return sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
}

double Vector::Magnitude() const
{
    return sqrt((x) * (x) + (y) * (y));
}

Vector Vector::Unit() const
{
    return Vector(this->x / Magnitude(), this->y / Magnitude());
}

void Vector::Rotate(const double theta)
{
    auto newX = cos(theta) * x - sin(theta) * y;
    auto newY = sin(theta) * x + cos(theta) * y;

    this->x = newX;
    this->y = newY;
}

Vector Vector::Rotate(const Vector& v, const double theta)
{
    return Vector(cos(theta) * v.x - sin(theta) * v.y, sin(theta) * v.x + cos(theta) * v.y);
}

Vector Vector::Project(const Vector& v, const Vector& w)
{
    return ((v * w) / w.Magnitude()) * w.Unit();
}

Vector Vector::Mirror(const Vector& v, const Vector& w)
{
    return 2 * Vector::Project(v, w) - v;
}

std::string Vector::ToString() const
{
    std::string ret = "(" + Formatter(x) + ", " + Formatter(y) + ")";
    return ret;
}

Vector Vector::operator+(const Vector& p) const
{
    return Vector(this->x + p.x, this->y + p.y);
}

Vector Vector::operator-(const Vector& p) const
{
    return Vector(this->x - p.x, this->y - p.y);
}

Vector Vector::operator+=(const Vector& p)
{
    this->x += p.x;
    this->y += p.y;

    return *this;
}

Vector Vector::operator-=(const Vector& p)
{
    this->x -= p.x;
    this->y -= p.y;

    return *this;
}

Vector Vector::operator*(double c)
{
    return Vector(this->x * c, this->y * c);
}

Vector Vector::operator*=(double c)
{
    this->x *= c;
    this->y *= c;

    return *this;
}

Vector operator*(double c, const Vector& p)
{
    return Vector(p.x * c, p.y * c);
}

double Vector::operator*(const Vector& p) const
{
    return this->x * p.x + this->y * p.y;
}

Vector& Vector::operator=(const Vector& other)
{
    // self-assignment guard
    if (this == &other)
        return *this;
    
    this->x = other.x;
    this->y = other.y;
    return *this;
}

bool operator==(const Vector& a, const Vector& b)
{
    return (a.x == b.x) && (a.y == b.y);
}

bool operator!=(const Vector& a, const Vector& b)
{
    return (a.x != b.x) || (a.y != b.y);
}
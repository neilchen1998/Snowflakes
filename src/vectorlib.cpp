#include <cmath>

#include "coordinate/vectorlib.hpp"

Vector::Vector() : x(0), y(0) {}

Vector::Vector(double x, double y) : x(x), y(y) {}

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

bool operator==(const Vector& a, const Vector& b)
{
    return (a.x == b.x) && (a.y == b.y);
}

bool operator!=(const Vector& a, const Vector& b)
{
    return (a.x != b.x) || (a.y != b.y);
}
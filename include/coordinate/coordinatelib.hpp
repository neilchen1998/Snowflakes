// reference: https://cplusplus.com/forum/beginner/165205/

#ifndef INCLUDE_COORDINATE_COORDINATELIB_H_
#define INCLUDE_COORDINATE_COORDINATELIB_H_

struct Point
{
    double x, y;

    Point();

    Point(double, double);

    /// @brief 
    /// @param other 
    /// @return 
    double Distance(const Point& other);

    /// @brief 
    /// @return 
    double Magnitude() const;

    /// @brief Get the unit vector
    /// @return the unit vector
    Point Unit() const;

    /// @brief Adding two points
    /// @param p the other point
    /// @return the sum of the two points
    Point operator+(const Point& p);

    /// @brief Subtracting two points
    /// @param p the other point
    /// @return the difference of the two points
    Point operator-(const Point& p);

    /// @brief Adding two points
    /// @param p the other point
    /// @return the sum of the two points
    Point operator+=(const Point& p);

    /// @brief Subtracting two points
    /// @param p the other point
    /// @return the difference of the two points
    Point operator-=(const Point& p);

    /// @brief Multiplying a point with a scalar value
    /// @param c a scalar
    /// @return the scaled vector
    Point operator*(double c);

    /// @brief Multiplying a point with a scalar value
    /// @param c a scalar
    /// @return the scaled vector
    Point operator*=(double c);

    /// @brief Performing inner product of two points
    /// @param p the other point
    /// @return the inner product of the two points
    double operator*(const Point& p) const;
};

/// @brief To make c * p work
/// @param c a scalar
/// @param p the other point
/// @return
Point operator*(double c, const Point& p);

/// @brief Checks if two points are the same
/// @param a point A
/// @param b point B
/// @return true if point A is equal to point B
bool operator==(const Point& a, const Point& b);

/// @brief Compares two points
/// @param a point A
/// @param b point B
/// @return true if point A is not equal to point B
bool operator!=(const Point& a, const Point& b);

#endif  // INCLUDE_COORDINATE_COORDINATELIB_H_

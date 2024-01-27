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
};

#endif  // INCLUDE_COORDINATE_COORDINATELIB_H_

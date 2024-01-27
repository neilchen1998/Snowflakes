// reference: https://cplusplus.com/forum/beginner/165205/

#ifndef INCLUDE_COORDINATE_VECTORLIB_H_
#define INCLUDE_COORDINATE_VECTORLIB_H_

struct Vector
{
    /// @brief 
    double x, y;

    /// @brief Contructor
    Vector();

    /// @brief Contructor
    /// @param  x
    /// @param  y
    Vector(double x, double y);

    /// @brief 
    /// @param other 
    /// @return 
    double Distance(const Vector& other);

    /// @brief 
    /// @return 
    double Magnitude() const;

    /// @brief Get the unit vector
    /// @return the unit vector
    Vector Unit() const;

    /// @brief Adding two Vectors
    /// @param p the other Vector
    /// @return the sum of the two Vectors
    Vector operator+(const Vector& p) const;

    /// @brief Subtracting two Vectors
    /// @param p the other Vector
    /// @return the difference of the two Vectors
    Vector operator-(const Vector& p) const;

    /// @brief Adding two Vectors
    /// @param p the other Vector
    /// @return the sum of the two Vectors
    Vector operator+=(const Vector& p);

    /// @brief Subtracting two Vectors
    /// @param p the other Vector
    /// @return the difference of the two Vectors
    Vector operator-=(const Vector& p);

    /// @brief Multiplying a Vector with a scalar value
    /// @param c a scalar
    /// @return the scaled vector
    Vector operator*(double c);

    /// @brief Multiplying a Vector with a scalar value
    /// @param c a scalar
    /// @return the scaled vector
    Vector operator*=(double c);

    /// @brief Performing inner product of two Vectors
    /// @param p the other Vector
    /// @return the inner product of the two Vectors
    double operator*(const Vector& p) const;
};

/// @brief To make c * p work
/// @param c a scalar
/// @param p the other Vector
/// @return
Vector operator*(double c, const Vector& p);

/// @brief Checks if two Vectors are the same
/// @param a Vector A
/// @param b Vector B
/// @return true if Vector A is equal to Vector B
bool operator==(const Vector& a, const Vector& b);

/// @brief Compares two Vectors
/// @param a Vector A
/// @param b Vector B
/// @return true if Vector A is not equal to Vector B
bool operator!=(const Vector& a, const Vector& b);

#endif  // INCLUDE_COORDINATE_VECTORLIB_H_

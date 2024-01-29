// reference: https://cplusplus.com/forum/beginner/165205/

#ifndef INCLUDE_COORDINATE_VECTORLIB_H_
#define INCLUDE_COORDINATE_VECTORLIB_H_

struct Vector
{
    double x, y;

    /// @brief Contructor
    Vector();

    /// @brief Contructor
    /// @param  x x value
    /// @param  y y value
    Vector(double x, double y);

    /// @brief Copy constructor
    /// @param other the other vector
    Vector(const Vector& other);

    /// @brief The Euclidean distance between itself and the other vector
    /// @param other the other vector
    /// @return the Euclidean distance between the two
    double Distance(const Vector& other);

    /// @brief The length of itself
    /// @return the length
    double Magnitude() const;

    /// @brief Get the unit vector
    /// @return the unit vector
    Vector Unit() const;

    /// @brief Rotating itself with theta
    /// @param theta the rotation angle in radian
    void Rotate(const double theta);

    /// @brief Rotating a vector with theta
    /// @param theta the rotation angle in radian
    /// @return the new vector after rotation
    static Vector Rotate(const Vector& v, const double theta);

    /// @brief Calculate the projected vector of vector v along vector w
    /// @param v the original vector
    /// @param w the norm vector
    /// @return the projected vector
    static Vector Project(const Vector& v, const Vector& w);

    /// @brief Calculate the mirrored vector of vector v along vector w
    /// @param v the original vector
    /// @param w the norm vector
    /// @return the new vector after mirrored
    static Vector Mirror(const Vector& v, const Vector& w);

    /// @brief Adding two Vectors
    /// @param other the other Vector
    /// @return the sum of the two Vectors
    Vector operator+(const Vector& other) const;

    /// @brief Subtracting two Vectors
    /// @param other the other Vector
    /// @return the difference of the two Vectors
    Vector operator-(const Vector& other) const;

    /// @brief Adding two Vectors
    /// @param other the other Vector
    /// @return the sum of the two Vectors
    Vector operator+=(const Vector& other);

    /// @brief Subtracting two Vectors
    /// @param other the other Vector
    /// @return the difference of the two Vectors
    Vector operator-=(const Vector& other);

    /// @brief Multiplying a Vector with a scalar value
    /// @param c a scalar
    /// @return the scaled vector
    Vector operator*(double c);

    /// @brief Multiplying a Vector with a scalar value
    /// @param c a scalar
    /// @return the scaled vector
    Vector operator*=(double c);

    /// @brief Performing inner product of two Vectors
    /// @param other the other Vector
    /// @return the inner product of the two Vectors
    double operator*(const Vector& other) const;

    /// @brief Overloaded assignment operator
    /// @param other 
    /// @return 
    Vector& operator=(const Vector& other);
};

/// @brief To make c * other work
/// @param c a scalar
/// @param other the other Vector
/// @return
Vector operator*(double c, const Vector& other);

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

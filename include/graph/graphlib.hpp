#ifndef INCLUDE_GRAPH_GRAPHLIB_H_
#define INCLUDE_GRAPH_GRAPHLIB_H_

#include <string>
#include <vector>

#include <opencv2/core/base.hpp>
#include "coordinate/vectorlib.hpp"

struct Circle
{
    Vector c;
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned int radius;

    Circle() : c(0.0, 0.0), r(255), g(255), b(255), radius(0) {}
    Circle(Vector c, unsigned char r, unsigned char g, unsigned char b, unsigned int radius) : c(c), r(r), g(g), b(b), radius(radius) {}

    void SetColour(unsigned char r, unsigned g, unsigned b)
    {
        this->r = r;
        this->g = g;
        this->b = b;
    }
};

/// @brief Displays the image using OpenCV
/// @param windowName the name of the window
/// @param img the image (OpenCV format)
void DisplayImage(const std::string& windowName, cv::Mat& img);

/// @brief Draws all circles in the vector container on the canvas
/// @param img the canvas
/// @param circles a vector of circles
void DrawCircles(cv::Mat& img, const std::vector<Circle>& circles);

/// @brief Draw a fern
/// @param img the canvas
/// @param v the direction vector of the arm
/// @param armLength the length of the arm
/// @param armWidth the width of the arm
/// @param nodeLength the distance betweeen two branches
/// @param branchLength the length of the branch
/// @param theta the angle between the branch and the arm
/// @param rate the discount rate
void DrawFern(cv::Mat& img, const Vector& v, const int armLength, const int armWidth, const int nodeLength, const int branchLength, const double theta, const double rate);

/// @brief Draw a Radiating Dendrites snowflake
/// @param img the canvas
/// @param v the direction vector of the arm
/// @param armLength the length of the arm
/// @param armWidth the width of the arm
/// @param nodeLength the distance betweeen two branches
/// @param branchLength the length of the branch
/// @param theta the angle between the branch and the arm
/// @param rate the discount rate
void DrawRadiatingDendriteSnowflake(cv::Mat& img, const Vector& v, const int armLength, const int armWidth, const int nodeLength, const int branchLength, const double theta, const double rate);

/// @brief Draw a Crystal snowflake
/// @param img the canvas
/// @param numCrystals the number of circles per arm
void DrawCrystalSnowflake(cv::Mat& img, const int numCrystals, int radiusHigh, int radiusLow, const Vector& mirror);

/// @brief Draw a hexagon
/// @param img the canvas
/// @param v the orientation of the hexagon
/// @param side the length of the side
/// @param offset the offset
void DrawHexagon(cv::Mat& img, const Vector& v, const int side, const Vector& offset = Vector(0, 0));

/// @brief Draw a Stellar Plate snowflake
/// @param img the canvas
/// @param v the direction of the mother hexagon
/// @param motherSide the lenght of the mother hexagon
/// @param sonSide the length of the son hexagon
void DrawStellarPlateSnowflake(cv::Mat& img, const Vector& v, const int motherSide, const int sonSide);

/// @brief Draw a Triangular Crystal snowflake
/// @param img the canvas
/// @param dir the direction of the main triangle
/// @param motherTriangleR the radius of the circumscribe of the mother triangle
/// @param sonTriangleR the radius of the circumscribe of the son triangle
/// @param radius the radius of the circle at the vertex
void DrawTriangularCrystalSnowflake(cv::Mat& img, const Vector& dir, const int motherTriangleR, const int sonTriangleR, const int radius);

/// @brief Saves the image using OpenCV
/// @param filename the filename
/// @param img the image
/// @return true if the file has been saved successfully
bool SaveImage(const std::string& filename, cv::Mat& img);

/// @brief Put label on the canvas
/// @param img the canvas
/// @param label the label
void PutLabel(cv::Mat& img, const std::string& label);

#endif  // INCLUDE_GRAPH_GRAPHLIB_H_

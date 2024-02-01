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
/// @param v the direction of the arm
/// @param numCrystals the number of circles per arm
void DrawCrystalSnowflake(cv::Mat& img, const Vector& v, const int numCrystals);

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

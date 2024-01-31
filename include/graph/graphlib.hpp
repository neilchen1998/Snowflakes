#ifndef INCLUDE_GRAPH_GRAPHLIB_H_
#define INCLUDE_GRAPH_GRAPHLIB_H_

#include <string>
#include <vector>

#include <opencv2/core/base.hpp>
#include "coordinate/vectorlib.hpp"

#define WHITE CV_RGB(255, 255, 255)
#define LIGHT_SKY_BLUE CV_RGB(153, 204, 255)
#define SALMON CV_RGB(250, 128, 114)

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

/// @brief Draw the backbone of a snowflake
/// @param img the canvas
/// @param numArms the number of rotations
void DrawBackbone(cv::Mat& img, const Vector& v, const int length, const int numArms);

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

/// @brief Renders an image of circles and mirrored circles
/// @param img the canvas
/// @param circles the vector container contains all circles
/// @param numArms the number of rotations
/// @param mirror the mirror vector
void RenderImage(cv::Mat& img, const std::vector<Circle>& circles, const int numArms, const Vector& mirror = Vector(1, 1));

/// @brief Saves the image using OpenCV
/// @param filename the filename
/// @param img the image
/// @return true if the file has been saved successfully
bool SaveImage(const std::string& filename, cv::Mat& img);

#endif  // INCLUDE_GRAPH_GRAPHLIB_H_

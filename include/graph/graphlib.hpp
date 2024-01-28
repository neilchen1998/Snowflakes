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
};

/// @brief Displays the image using OpenCV
/// @param windowName the name of the window
/// @param img the image (OpenCV format)
void DisplayImage(const std::string& windowName, cv::Mat& img);

/// @brief Draws all circles in the vector container on the canvas
/// @param img the canvas
/// @param circles a vector of circles
void DrawAllCircles(cv::Mat& img, const std::vector<Circle>& circles);

/// @brief Saves the image using OpenCV
/// @param filename the filename
/// @param img the image
/// @return true if the file has been saved successfully
bool SaveImage(const std::string& filename, cv::Mat& img);

#endif  // INCLUDE_GRAPH_GRAPHLIB_H_

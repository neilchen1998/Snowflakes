#include <filesystem>
#include <algorithm>

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include "graph/graphlib.hpp"
#include "coordinate/vectorlib.hpp"

#define FILLED -1
#define ROWS 1024
#define COLS 1024
#define CENTER (ROWS/2)

#define PI 3.14159265
#define DEG_TO_RAD(deg) ((deg) * PI / 180.0 )

void DisplayImage(const std::string& windowName, cv::Mat& img)
{
    cv::imshow(windowName, img);
    cv::waitKey(0);

    return;
}

void DrawCircles(cv::Mat& img, const std::vector<Circle>& circles)
{
    auto itr = circles.cbegin();
    while (itr != circles.cend())
    {
        cv::circle(img, cv::Point(itr->c.x + CENTER, itr->c.y + CENTER), itr->radius, CV_RGB(itr->r, itr->g, itr->b), FILLED);
        ++itr;
    }
}

void DrawBackbone(cv::Mat& img, const Vector& v, const int length, const int numRotations)
{
    const unsigned char THETA = 360 / numRotations;
    for (int rotation = 0; rotation < numRotations; rotation++)
    {
        Vector dir = length * Vector::Rotate(v, DEG_TO_RAD(THETA * rotation));
        cv::line(img, cv::Point(CENTER, CENTER), cv::Point(dir.x + CENTER, dir.y + CENTER), CV_RGB(153, 204, 255), 5);
    }
}

void DrawRotatedCircles(cv::Mat& img, const std::vector<Circle>& circles, const int theta, const int spin)
{
    auto itr = circles.cbegin();
    while (itr != circles.cend())
    {
        auto focus = Vector::Rotate(itr->c, DEG_TO_RAD(theta * spin));
        cv::circle(img, cv::Point(focus.x + CENTER, focus.y + CENTER), itr->radius, CV_RGB(itr->r, itr->g, itr->b), FILLED);
        ++itr;
    }
}

void RenderImage(cv::Mat& img, const std::vector<Circle>& circles, const int numRotations, const Vector& mirror)
{
    const unsigned char THETA = 360 / numRotations;

    // draws the original circles
    for (int rotation = 0; rotation < numRotations; rotation++)
    {
        DrawRotatedCircles(img, circles, THETA, rotation);
    }

    // calculates the circles mirror w.r.t. the mirror vector
    std::vector<Circle> tmp(circles.size());
    std::transform(circles.begin(), circles.end(), tmp.begin(), [&](const Circle& circle)
    {
        Circle mirroredCircle = circle;
        mirroredCircle.c = Vector::Mirror(circle.c, mirror);
        return mirroredCircle;
    });

    // draw the mirrored circles
    for (int rotation = 0; rotation < numRotations; rotation++)
    {
        DrawRotatedCircles(img, tmp, THETA, rotation);
    }
}

bool SaveImage(const std::string& filename, cv::Mat& img)
{
    // checks if the folder exists
    std::filesystem::path p(filename);
    if (std::filesystem::exists(p.parent_path()))
    {
        cv::imwrite(filename, img);
        return true;
    }
    else
        return false;
}

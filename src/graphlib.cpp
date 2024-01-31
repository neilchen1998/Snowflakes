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

void DrawBackbone(cv::Mat& img, const Vector& v, const int length, const int numArms)
{
    const unsigned char THETA = 360 / numArms;
    for (int rotation = 0; rotation < numArms; rotation++)
    {
        Vector dir = length * Vector::Rotate(v, DEG_TO_RAD(THETA * rotation));
        cv::line(img, cv::Point(CENTER, CENTER), cv::Point(dir.x + CENTER, dir.y + CENTER), LIGHT_SKY_BLUE, 5);
    }
}

void DrawFern(cv::Mat& img, const Vector& v, const int armLength, const int armWidth, const int nodeLength, const int branchLength, const double theta, const double rate)
{
    // draws the main arm
    cv::line(img, cv::Point(CENTER, CENTER), cv::Point(armLength * v.x + CENTER, armLength * v.y + CENTER), LIGHT_SKY_BLUE, 5);

    // draw the branches
    const int N = armLength / nodeLength;
    double alpha = 1;
    for (int i = 0; i < N; i++)
    {
        // draw the branch
        Vector start = (i * nodeLength) * v;
        Vector end = alpha * branchLength * Vector::Rotate(v, theta) + start;
        cv::line(img, cv::Point(start.x + CENTER, start.y + CENTER), cv::Point(end.x + CENTER, end.y + CENTER), SALMON, 5);

        // draw the mirrored branch
        end = Vector::Mirror(end, v);
        cv::line(img, cv::Point(start.x + CENTER, start.y + CENTER), cv::Point(end.x + CENTER, end.y + CENTER), SALMON, 5);

        // apply the discount rate
        alpha *= rate;
    }
}

void DrawRadiatingDendriteSnowflake(cv::Mat& img, const Vector& v, const int armLength, const int armWidth, const int nodeLength, const int branchLength, const double theta, const double rate)
{
    for (int rotation = 0; rotation < 6; ++rotation)
    {
        DrawFern(img, Vector::Rotate(v, DEG_TO_RAD(60 * rotation)), armLength, armWidth, nodeLength, branchLength, theta, rate);
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

void RenderImage(cv::Mat& img, const std::vector<Circle>& circles, const int numArms, const Vector& mirror)
{
    const unsigned char THETA = 360 / numArms;

    // draws the original circles
    for (int rotation = 0; rotation < numArms; rotation++)
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
    for (int rotation = 0; rotation < numArms; rotation++)
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

#include <filesystem>
#include <algorithm>
#include <vector>
#include <array>

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include "graph/graphlib.hpp"
#include "coordinate/vectorlib.hpp"
#include "coordinate/generatorlib.hpp"
#include "math/mathlib.hpp"

// OpenCV
#define FILLED -1
#define ROWS 1024
#define COLS 1024
#define CENTER (ROWS/2)

// snowflake properties
#define NUM_ARMS 6

// colours
#define WHITE CV_RGB(255, 255, 255)
#define LIGHT_SKY_BLUE CV_RGB(153, 204, 255)
#define SALMON CV_RGB(250, 128, 114)

// algebra
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

void DrawBackbone(cv::Mat& img, const Vector& v, const int length)
{
    const unsigned char THETA = 360 / NUM_ARMS;
    for (int rotation = 0; rotation < NUM_ARMS; rotation++)
    {
        Vector dir = length * Vector::Rotate(v, DEG_TO_RAD(THETA * rotation));
        cv::line(img, cv::Point(CENTER, CENTER), cv::Point(dir.x + CENTER, dir.y + CENTER), WHITE, 5);
    }
}

void DrawFern(cv::Mat& img, const Vector& v, const int armLength, const int armWidth, const int nodeLength, const int branchLength, const double theta, const double rate)
{
    // draws the main arm
    cv::line(img, cv::Point(CENTER, CENTER), cv::Point(armLength * v.x + CENTER, armLength * v.y + CENTER), WHITE, 5);

    // draw the branches
    const int N = armLength / nodeLength;
    double alpha = 1;
    for (int i = 0; i < N; i++)
    {
        // draw the branch
        Vector start = (i * nodeLength) * v;
        Vector end = alpha * branchLength * Vector::Rotate(v, theta) + start;
        cv::line(img, cv::Point(start.x + CENTER, start.y + CENTER), cv::Point(end.x + CENTER, end.y + CENTER), WHITE, armWidth);

        // draw the mirrored branch
        end = Vector::Mirror(end, v);
        cv::line(img, cv::Point(start.x + CENTER, start.y + CENTER), cv::Point(end.x + CENTER, end.y + CENTER), WHITE, 5);

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

void DrawCrystalSnowflake(cv::Mat& img, const int numCrystals, int radiusHigh, int radiusLow, const Vector& mirror)
{
    std::vector<Circle> circles(numCrystals * 2 * NUM_ARMS);
    circles[0].c = Vector(0, 0);

    // generates particles
    for (int i = 1; i < numCrystals; i++)
    {
        Vector start = circles[i - 1].c;
        int radiusStart = circles[i - 1].radius;
        int radiusNew = boost_uniform_int_distribution(radiusHigh, radiusLow);
        Vector cNew = GenerateNextCircle(start, radiusStart, Vector(1, boost_normal_distribution(1, 0.3)), radiusNew);
        circles[i].c = cNew;
        circles[i].radius = radiusNew;
    }

    // draws all circles on the canvas
    const unsigned char THETA = 360 / NUM_ARMS;
    // draws the original circles
    for (int rotation = 0; rotation < NUM_ARMS; rotation++)
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
    for (int rotation = 0; rotation < NUM_ARMS; rotation++)
    {
        DrawRotatedCircles(img, tmp, THETA, rotation);
    }
}

void DrawHexagon(cv::Mat& img, const Vector& v, const int side, const Vector& offset)
{
    // defines the points (vertices) of the hexagon
    std::vector<cv::Point> points(6);

    // finds the first vertice
    Vector r = side * v;

    // figures out all the vertices
    auto itr = points.begin();
    while (itr != points.end())
    {
        *itr = cv::Point(r.x + offset.x + CENTER, r.y + offset.y + CENTER);

        // rotate the vector
        r.Rotate(DEG_TO_RAD(60));
        ++itr;
    }

    // puts the points into a vector of vectors
    std::vector<std::vector<cv::Point>> pts(1);
    pts[0] = points;

    // draws the polygon on the image
    cv::fillPoly(img, pts, WHITE);
}

void DrawStellarPlateSnowflake(cv::Mat& img, const Vector& v, const int motherSide, const int sonSide)
{
    DrawHexagon(img, v, motherSide);

    Vector offset = motherSide * v;

    for (int i = 0; i < 6; i++)
    {
        DrawHexagon(img, v, sonSide, offset);
        offset.Rotate(DEG_TO_RAD(60));
    }
}

void DrawTriangularCrystalSnowflake(cv::Mat& img, const Vector& dir, const int motherTriangleR, const int sonTriangleR, const int radius)
{
    // defines the points (vertices) of the main body
    std::vector<cv::Point> points(6);
    Vector v = (motherTriangleR - sonTriangleR) * dir;
    Vector tmp;
    
    // the first vertex
    tmp = sonTriangleR * Vector::Rotate(v.Unit(), DEG_TO_RAD(-120)) + v;
    points[0] = cv::Point(tmp.x + CENTER, tmp.y + CENTER);
    cv::circle(img, cv::Point(tmp.x + CENTER, tmp.y + CENTER), radius, WHITE, FILLED);
    tmp = sonTriangleR * Vector::Rotate(v.Unit(), DEG_TO_RAD(120)) + v;
    points[1] = cv::Point(tmp.x + CENTER, tmp.y + CENTER);
    cv::circle(img, cv::Point(tmp.x + CENTER, tmp.y + CENTER), radius, WHITE, FILLED);

    // the second vertex
    v.Rotate(DEG_TO_RAD(120));
    tmp = sonTriangleR * Vector::Rotate(v.Unit(), DEG_TO_RAD(-120)) + v;
    points[2] = cv::Point(tmp.x + CENTER, tmp.y + CENTER);
    cv::circle(img, cv::Point(tmp.x + CENTER, tmp.y + CENTER), radius, WHITE, FILLED);
    tmp = sonTriangleR * Vector::Rotate(v.Unit(), DEG_TO_RAD(120)) + v;
    points[3] = cv::Point(tmp.x + CENTER, tmp.y + CENTER);
    cv::circle(img, cv::Point(tmp.x + CENTER, tmp.y + CENTER), radius, WHITE, FILLED);

    // the third vertex
    v.Rotate(DEG_TO_RAD(120));
    tmp = sonTriangleR * Vector::Rotate(v.Unit(), DEG_TO_RAD(-120)) + v;
    points[4] = cv::Point(tmp.x + CENTER, tmp.y + CENTER);
    cv::circle(img, cv::Point(tmp.x + CENTER, tmp.y + CENTER), radius, WHITE, FILLED);
    tmp = sonTriangleR * Vector::Rotate(v.Unit(), DEG_TO_RAD(120)) + v;
    points[5] = cv::Point(tmp.x + CENTER, tmp.y + CENTER);
    cv::circle(img, cv::Point(tmp.x + CENTER, tmp.y + CENTER), radius, WHITE, FILLED);

    // puts the points into a vector of vectors
    std::vector<std::vector<cv::Point>> pts(1);
    pts[0] = points;

    // draws the polygon on the image
    cv::fillPoly(img, pts, WHITE);
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

void PutLabel(cv::Mat& img, const std::string& label)
{
    int fontFace = cv::FONT_HERSHEY_PLAIN;
    double fontScale = 2;
    int thickness = 2;
    int baseline = 0;

    cv::Size textSize = cv::getTextSize(label, fontFace, fontScale, thickness, &baseline);
    baseline += thickness;
    
    // calculate the center the text
    cv::Point textOrg(0.5 * (img.cols - textSize.width), 0.5 * textSize.height + 50);

    // put the text on the image
    cv::putText(img, label, textOrg, cv::FONT_HERSHEY_PLAIN, fontScale, LIGHT_SKY_BLUE, thickness, 2);
}

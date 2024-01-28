#include <iostream>
#include <stdio.h>
#include <vector>

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include "math/mathlib.hpp"
#include "graph/graphlib.hpp"
#include "coordinate/generatorlib.hpp"
#include "coordinate/vectorlib.hpp"

#define ROWS 1024
#define COLS 1024
#define CENTER (ROWS/2)

#define PI 3.14159265
#define DEG_TO_RAD(deg) ((deg) * PI / 180.0 )

int main()
{   
    // create a black canvas
    cv::Mat img(ROWS, COLS, CV_8UC3, CV_RGB(0, 0, 0));

    // generates particles
    constexpr size_t NUM_CIRCLES = 50;
    std::vector<Circle> circles(NUM_CIRCLES * 12);
    circles[0].c = Vector(0, 0);
    for (size_t i = 1; i < NUM_CIRCLES; i++)
    {
        Vector start = circles[i - 1].c;
        int radiusStart = circles[i - 1].radius;
        Vector dir = Vector(1, boost_normal_distribution(1));
        int radiusNew = boost_uniform_int_distribution(10);
        Vector cNew = GenerateNextCircle(start, radiusStart, dir, radiusNew);
        circles[i].c = cNew;
        circles[i].radius = radiusNew;
    }

    for (size_t spin = 1; spin < 12; spin++)
    {
        for (size_t i = 0; i < NUM_CIRCLES; i++)
        {
            circles[spin * NUM_CIRCLES + i].c = Vector::Rotate(circles[i].c, DEG_TO_RAD(30*spin));
            circles[spin * NUM_CIRCLES + i].radius = circles[i].radius;
        }
    }
    

    // draws all circles on the canvas
    DrawAllCircles(img, circles);

    DisplayImage("Image", img);

    return EXIT_SUCCESS;
}
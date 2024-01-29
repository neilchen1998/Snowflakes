#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>

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

#define DEBUG_MODE 1

int main()
{   
    bool canSave = true;
    constexpr unsigned char NUM_RENDERS = (DEBUG_MODE) ? 5 : 10;
    // renders N images
    for (unsigned char render = 0; render < NUM_RENDERS; render++)
    {
        // creates a black canvas
        cv::Mat img(ROWS, COLS, CV_8UC3, CV_RGB(0, 0, 0));
        constexpr size_t NUM_CIRCLES = 50;
        constexpr unsigned char NUM_SPINS = 12;
        constexpr unsigned char THETA = 360 / NUM_SPINS;
        std::vector<Circle> circles(NUM_CIRCLES * NUM_SPINS);
        circles[0].c = Vector(0, 0);
        
        // generates particles
        for (size_t i = 1; i < NUM_CIRCLES; i++)
        {
            Vector start = circles[i - 1].c;
            int radiusStart = circles[i - 1].radius;
            Vector dir = Vector(1, boost_normal_distribution(1));
            int radiusNew = boost_uniform_int_distribution(7);
            Vector cNew = GenerateNextCircle(start, radiusStart, dir, radiusNew);
            circles[i].c = cNew;
            circles[i].radius = radiusNew;
        }

        for (size_t spin = 1; spin < NUM_SPINS; spin++)
        {
            for (size_t i = 0; i < NUM_CIRCLES; i++)
            {
                circles[spin * NUM_CIRCLES + i].c = Vector::Rotate(circles[i].c, DEG_TO_RAD(THETA*spin));
                circles[spin * NUM_CIRCLES + i].radius = circles[i].radius;
            }
        }

        // draws all circles on the canvas
        DrawAllCircles(img, circles);

        #if DEBUG_MODE

            DisplayImage("image", img);

        #else
            // save image
            std::string filepath("outputs/");
            std::string filename = "image-" + std::to_string(render) + ".jpg";
            canSave = SaveImage(filepath + filename, img);
            if (!canSave)
                return EXIT_FAILURE;
        #endif
    }

    return EXIT_SUCCESS;
}

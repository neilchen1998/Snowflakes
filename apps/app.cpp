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
    constexpr unsigned char NUM_RENDERS = (DEBUG_MODE) ? 1 : 10;
    // renders N images
    for (unsigned char render = 0; render < NUM_RENDERS; render++)
    {
        // creates a black canvas
        cv::Mat img(ROWS, COLS, CV_8UC3, CV_RGB(0, 0, 0));

        DrawCrystalSnowflake(img, Vector(1, 1), boost_normal_distribution(45, 10));

        // DrawRadiatingDendriteSnowflake(img, Vector(1, boost_normal_distribution(1, 0.3)), 200, boost_normal_distribution(5, 1), 20, 50 , DEG_TO_RAD(boost_normal_distribution(60, 10)), boost_normal_distribution(0.7, 0.1));

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

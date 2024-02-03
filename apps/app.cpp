#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>

#include "opencv2/imgproc.hpp"  // CV_RGB

#include "math/mathlib.hpp"
#include "graph/graphlib.hpp"
#include "coordinate/generatorlib.hpp"
#include "coordinate/vectorlib.hpp"

#define ROWS 1024
#define COLS 1024

#define DEBUG_MODE 1

enum snowflakeType { Crystal, RadiatingDendrite, StellarPlate, TriangularCrystal };

int main()
{   
    constexpr unsigned char NUM_RENDERS = (DEBUG_MODE) ? 1 : 10;

    std::string snowflakeName("Triangular-Crystal-Snowflake");

    bool canSave;

    // renders snowflakes
    for (unsigned char render = 0; render < NUM_RENDERS; render++)
    {
        // creates a black canvas
        cv::Mat img(ROWS, COLS, CV_8UC3, CV_RGB(0, 0, 0));

        const Vector v(boost_normal_distribution(1, 0.1), boost_normal_distribution(1, 0.1));

        int motherTriangleR = boost_normal_distribution(330, 30);
        int sonTriangleR = boost_normal_distribution(80, 10);
        int radius = boost_normal_distribution(50, 10);

        // makes sure motherSide is greater than sonSide
        motherTriangleR = (motherTriangleR <= sonTriangleR) ? sonTriangleR + 100 : motherTriangleR;

        DrawTriangularCrystalSnowflake(img, v, motherTriangleR, sonTriangleR, radius);

        // // put parameters on the image
        // PutLabel(img, label);

        #if DEBUG_MODE

            DisplayImage("image", img);

        #else
            // save image
            std::string filepath("outputs/");
            std::string filename = snowflakeName + "_" + std::to_string(render) + ".jpg";
            canSave = SaveImage(filepath + filename, img);
            if (!canSave)
                return EXIT_FAILURE;
        #endif
    }

    return EXIT_SUCCESS;
}

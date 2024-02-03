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
#include "helper/fmtlib.hpp"

#define ROWS 1024
#define COLS 1024

#define DEBUG_MODE 0

enum snowflakeType { Crystal, RadiatingDendrite, StellarPlate };

int main()
{   
    constexpr unsigned char NUM_RENDERS = (DEBUG_MODE) ? 1 : 10;

    std::string snowflakeName("Stellar-Plate-Snowflake");

    bool canSave;

    // renders snowflakes
    for (unsigned char render = 0; render < NUM_RENDERS; render++)
    {
        // creates a black canvas
        cv::Mat img(ROWS, COLS, CV_8UC3, CV_RGB(0, 0, 0));

        const Vector v(boost_normal_distribution(1, 0.1), boost_normal_distribution(1, 0.1));
        const Vector w(boost_normal_distribution(1, 0.1), boost_normal_distribution(1, 0.1));

        int motherSide = boost_normal_distribution(100, 30);
        int sonSide = boost_normal_distribution(40, 10);

        // makes sure motherSide is greater than sonSide
        motherSide = (motherSide <= sonSide) ? sonSide + 10 : motherSide;

        DrawStellarPlateSnowflake(img, v.Unit(), w, motherSide, sonSide);

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

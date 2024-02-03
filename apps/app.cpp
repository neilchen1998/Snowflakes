#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>

#include "opencv2/imgproc.hpp"  // CV_RGB

#include "math/mathlib.hpp"
#include "graph/graphlib.hpp"
#include "coordinate/generatorlib.hpp"
#include "coordinate/vectorlib.hpp"
#include "helper/fmtlib.hpp"

#define ROWS 1024
#define COLS 1024
#define CENTER (ROWS/2)

#define PI 3.14159265
#define DEG_TO_RAD(deg) ((deg) * PI / 180.0 )

#define DEBUG_MODE 1

enum snowflakeType { crystal, radiatingDendrite };

int main(int argc, char* argv[])
{   
    bool canSave = true;
    constexpr unsigned char NUM_RENDERS = (DEBUG_MODE) ? 1 : 10;

    unsigned char selectedSnowflakeType = radiatingDendrite;
    std::string snowflakeName;

    switch (selectedSnowflakeType)
    {
    case crystal:
    {
        const int mean = 45, sd = 10;
        int radiusHigh = 7;
        int radiusLow = 2;

        // renders snowflakes
        for (unsigned char render = 0; render < NUM_RENDERS; render++)
        {
            // creates a black canvas
            cv::Mat img(ROWS, COLS, CV_8UC3, CV_RGB(0, 0, 0));

            int numCrystals = boost_normal_distribution(mean, sd);
            const Vector mirror(boost_normal_distribution(1, 0.1), boost_normal_distribution(1, 0.1));

            DrawCrystalSnowflake(img, Vector(1, 1), numCrystals, radiusHigh, radiusLow, mirror);

            snowflakeName = "Crystal-Snowflake";

            std::string label = "# of crystals: " + std::to_string(numCrystals) + " mirror: " + mirror.ToString();

            // put parameters on the image
            PutLabel(img, label);

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
    }

        break;

    case radiatingDendrite:
    {
        const int mean = 200, sd = 20;

        // renders snowflakes
        for (unsigned char render = 0; render < NUM_RENDERS; render++)
        {
            // creates a black canvas
            cv::Mat img(ROWS, COLS, CV_8UC3, CV_RGB(0, 0, 0));

            const Vector mirror(boost_normal_distribution(1, 0.1), boost_normal_distribution(1, 0.1));
            const int armLength = boost_normal_distribution(mean, sd);
            const int armWidth = boost_normal_distribution(5, 1);
            const int nodeLength = 20;
            const int branchLength = 50;
            const double theta = DEG_TO_RAD(boost_normal_distribution(60, 10));
            const double rate = boost_normal_distribution(0.8, 0.1);

            DrawRadiatingDendriteSnowflake(img, mirror, armLength, armWidth, 20, 50 , theta, rate);

            snowflakeName = "Radiating-Dendrite-Snowflake";

            std::string label = "armLength: " + std::to_string(armLength) + " armWidth: " + std::to_string(armWidth) + " theta: " + Formatter(theta) + " rate: " + Formatter(rate);

            // put parameters on the image
            PutLabel(img, label);

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
    }
        break;

    default:
        break;
    }

    return EXIT_SUCCESS;
}

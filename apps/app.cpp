#include <iostream> // std::cerr
#include <string>
#include <unordered_set>  // std::unordered_set
#include <string_view>  // std::string_view
#include <stdlib.h> // EXIT_SUCCESS, EXIT_FAILURE
#include <algorithm>    // std::min

#include <boost/program_options.hpp>    // boost::program_options
#include <opencv2/imgproc.hpp>  // CV_RGB

#include "math/mathlib.hpp"
#include "graph/graphlib.hpp"
#include "coordinate/generatorlib.hpp"
#include "coordinate/vectorlib.hpp"
#include "helper/fmtlib.hpp"
#include "helper/consolelib.hpp"

namespace po = boost::program_options;

#define ROWS 1024
#define COLS 1024
#define CENTER (ROWS/2)

#define PI 3.14159265
#define DEG_TO_RAD(deg) ((deg) * PI / 180.0 )

#define DEBUG_MODE 1

int main(int argc, char* argv[])
{
    std::string selectedSnowflake;
    std::string outputDir;
    unsigned int numImages;
    bool useDefaultValues;

    // creates options descriptions and default values
    po::options_description desc("Options:");
    desc.add_options()
        ("help,h", "Display this information")
        ("snowflake,s", po::value<std::string>(&selectedSnowflake)->value_name("<SNOWFLAKE_TYPE>")->default_value("crystal"), "the type of snowflake")
        ("output,o", po::value<std::string>(&outputDir)->value_name("<OUTPUT_DIR>")->default_value("outputs"), "the output directory")
        ("number,n", po::value<unsigned int>(&numImages)->value_name("<NUM_IMAGES>")->default_value(10), "number of images")
        ("default,d", po::value<bool>(&useDefaultValues)->value_name("<USE_DEFUALT_VALUES>")->default_value(true), "use default values");   // (<long name>,<short name>, <argument(s)>, <description>)

    // creates the variables map and stores the inputs to the map
    po::variables_map vm;

    // makes "snowflake" token be the positional option, i.e., token with no option name
    po::positional_options_description p;
    p.add("snowflake", -1);
    
    // checks if the user inputs are valid
    try
    {
        // parses the arguments and writes the variables according to the variables map
        po::store(po::command_line_parser(argc, argv).options(desc).positional(p).run(), vm);
        po::notify(vm);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }
    
    // checks if the user selects --help
    if (vm.count("help"))
    {
        std::cout << desc << "\n";
        return EXIT_FAILURE;
    }

    // checks if we have the user input snowflake type
    std::unordered_set<std::string_view> snowflakeOptions({"crystal", "radiating-dendrite", "stellar-plate", "triangular-crystal"});
    if (snowflakeOptions.find(selectedSnowflake) == snowflakeOptions.end())
    {
        std::cout << "Invalid input...\n";
        std::cout << "Please select one of the following snowflake types:\n";
        auto itr = snowflakeOptions.cbegin();
        while (itr != snowflakeOptions.cend())
        {
            std::cout << *itr << "\n";
            ++itr;
        }
        return EXIT_FAILURE;
    }

    // main programme
    bool canSave = true;
    if (selectedSnowflake == "crystal")
    {
        // default values
        int mean = 45;
        double sd = 10.0;
        int radiusHigh = 7;
        int radiusLow = 2;

        // gets inputs from the console
        if (!useDefaultValues)
        {
            if(!GetUserInput(mean, "mean", 5, 55) || !GetUserInput(sd, "the standard deviation of the number of crystal", 0.0, 10.0) \
            || !GetUserInput(radiusHigh, "the upper bound of the radius", 1, 10) || !GetUserInput(radiusLow, "the lower bound of the radius", 0, radiusHigh))
            {
                return EXIT_FAILURE;
            }
        }

        // renders snowflakes
        for (unsigned char render = 0; render < numImages; render++)
        {
            // creates a black canvas
            cv::Mat img(ROWS, COLS, CV_8UC3, CV_RGB(0, 0, 0));

            int numCrystals = static_cast<int>(std::max(boost_normal_distribution(mean, sd), 10.0));    // makes sure the value is at least 10
            const Vector mirror(boost_normal_distribution(1, 0.1), boost_normal_distribution(1, 0.1));

            DrawCrystalSnowflake(img, Vector(1, 1), numCrystals, radiusHigh, radiusLow, mirror);

            const std::string snowflakeName("Crystal-Snowflake");

            std::string label = "mirror vec: " + mirror.ToString();

            // put parameters on the image
            PutLabel(img, label);

            #if DEBUG_MODE

                DisplayImage("image", img);

                return EXIT_SUCCESS;

            #else
                // save image
                std::string filename = snowflakeName + "_" + std::to_string(render + 1) + ".jpg";
                canSave = SaveImage(outputDir + "/" + filename, img);
                if (!canSave)
                    return EXIT_FAILURE;
            #endif
        }
    }
    else if (selectedSnowflake == "radiating-dendrite")
    {
        // default values
        int mean = 200;
        double sd = 20.0;

        // gets inputs from the console
        if (!useDefaultValues)
        {
            if(!GetUserInput(mean, "mean", 150, 300) || !GetUserInput(sd, "the standard deviation of the number of crystal", 0.0, 30.0))
            {
                return EXIT_FAILURE;
            }
        }

        // renders snowflakes
        for (unsigned char render = 0; render < numImages; render++)
        {
            // creates a black canvas
            cv::Mat img(ROWS, COLS, CV_8UC3, CV_RGB(0, 0, 0));

            const Vector mirror(boost_normal_distribution(1, 0.1), boost_normal_distribution(1, 0.1));
            const int armLength = boost_normal_distribution(mean, sd);
            const int armWidth = boost_normal_distribution(5, 1);
            const int nodeLength = boost_uniform_int_distribution(25, 15);    // 20
            const int branchLength = boost_uniform_int_distribution(65, 20);    // 50
            const double theta = DEG_TO_RAD(boost_normal_distribution(60, 10));
            const double rate = boost_normal_distribution(0.8, 0.1);

            DrawRadiatingDendriteSnowflake(img, mirror, armLength, armWidth, nodeLength, branchLength, theta, rate);

            const std::string snowflakeName("Radiating-Dendrite-Snowflake");

            std::string label = "armLength: " + std::to_string(armLength) + " armWidth: " + std::to_string(armWidth) + " theta: " + Formatter(theta) + " rate: " + Formatter(rate);

            // put parameters on the image
            PutLabel(img, label);

            #if DEBUG_MODE

                DisplayImage("image", img);

                return EXIT_SUCCESS;

            #else
                std::string filename = snowflakeName + "_" + std::to_string(render + 1) + ".jpg";
                canSave = SaveImage(outputDir + "/" + filename, img);
                if (!canSave)
                    return EXIT_FAILURE;
            #endif
        }
    }
    else if (selectedSnowflake == "stellar-plate")
    {
        // default values
        int motherSideMean = 100, sonSideMean = 40;
        double motherSideSD = 30.0, sonSideSD = 10.0;

        // gets inputs from the console
        if (!useDefaultValues)
        {
            if(!GetUserInput(motherSideMean, "mean of the mother length", 150, 300) || !GetUserInput(motherSideSD, "the standard deviation of the mother length", 0.0, 30.0) || \
            !GetUserInput(sonSideMean, "mean of the son length", 60, static_cast<int>(std::min(motherSideMean - 2 * motherSideSD, 100.0))) || !GetUserInput(sonSideSD, "the standard deviation of the son length", 0.0, 0.5 * sonSideMean))
            {
                return EXIT_FAILURE;
            }
        }

        // renders snowflakes
        for (unsigned char render = 0; render < numImages; render++)
        {
            // creates a black canvas
            cv::Mat img(ROWS, COLS, CV_8UC3, CV_RGB(0, 0, 0));

            const Vector v(boost_normal_distribution(1, 0.1), boost_normal_distribution(1, 0.1));
            const Vector w(boost_normal_distribution(1, 0.1), boost_normal_distribution(1, 0.1));

            int motherSide = boost_normal_distribution(motherSideMean, motherSideSD);
            int sonSide = boost_normal_distribution(sonSideMean, sonSideSD);

            // makes sure motherSide is greater than sonSide
            motherSide = (motherSide <= sonSide) ? sonSide + 10 : motherSide;

            DrawStellarPlateSnowflake(img, v.Unit(), w, motherSide, sonSide);

            const std::string snowflakeName("Stellar-Plate-Snowflake");

            std::string label = "motherSide: " + std::to_string(motherSide) + " sonSide: " + std::to_string(sonSide);

            // put parameters on the image
            PutLabel(img, label);

            #if DEBUG_MODE

                DisplayImage(snowflakeName, img);

                return EXIT_SUCCESS;

            #else

                // save image
                std::string filename = snowflakeName + "_" + std::to_string(render + 1) + ".jpg";
                canSave = SaveImage(outputDir + "/" + filename, img);
                if (!canSave)
                    return EXIT_FAILURE;
            #endif
        }
    }
    else if (selectedSnowflake == "triangular-crystal")
    {
        // default values
        int motherSideMean = 330, sonSideMean = 80, radiusMean = 50;
        double motherSideSD = 30.0, sonSideSD = 10.0, radiusSD = 10.0;

        // gets inputs from the console
        if (!useDefaultValues)
        {
            if(!GetUserInput(motherSideMean, "mean of the mother length", 150, 300) || !GetUserInput(motherSideSD, "the standard deviation of the mother length", 0.0, 30.0) || \
            !GetUserInput(sonSideMean, "mean of the son length", 60, static_cast<int>(std::min(motherSideMean - 2 * motherSideSD, 100.0))) || !GetUserInput(sonSideSD, "the standard deviation of the son length", 0.0, 0.5 * sonSideMean) || \
            !GetUserInput(radiusMean, "mean of the radius", 20, 90) || !GetUserInput(sonSideSD, "the standard deviation of the radius", 0.0, 0.5 * radiusMean))
            {
                return EXIT_FAILURE;
            }
        }

        // renders snowflakes
        for (unsigned char render = 0; render < numImages; render++)
        {
            // creates a black canvas
            cv::Mat img(ROWS, COLS, CV_8UC3, CV_RGB(0, 0, 0));

            const Vector v(boost_normal_distribution(1, 0.1), boost_normal_distribution(1, 0.1));

            int motherTriangleR = boost_normal_distribution(motherSideMean, motherSideSD);
            int sonTriangleR = boost_normal_distribution(sonSideMean, sonSideSD);
            int radius = boost_normal_distribution(radiusMean, radiusSD);

            // makes sure motherSide is greater than sonSide
            motherTriangleR = (motherTriangleR <= sonTriangleR) ? sonTriangleR + 100 : motherTriangleR;

            DrawTriangularCrystalSnowflake(img, v, motherTriangleR, sonTriangleR, radius);

            std::string snowflakeName("Triangular-Crystal-Snowflake");

            std::string label = "motherTriR: " + std::to_string(motherTriangleR) + " sonTriR: " + std::to_string(sonTriangleR) + " radius: " + std::to_string(radius);

            // put parameters on the image
            PutLabel(img, label);

            #if DEBUG_MODE

                DisplayImage(snowflakeName, img);

                return EXIT_SUCCESS;

            #else
                // save image
                std::string filename = snowflakeName + "_" + std::to_string(render + 1) + ".jpg";
                canSave = SaveImage(outputDir + "/" + filename, img);
                if (!canSave)
                    return EXIT_FAILURE;
            #endif
        }
    }

    if (canSave)
    {
        std::cout << "All files have been saved successfully!" << std::endl;
    }

    return EXIT_SUCCESS;
}